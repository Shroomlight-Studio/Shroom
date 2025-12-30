#include "VulkanRendererAPI.h"

#include "Shroom/Core/Application.h"

#include <SDL3/SDL_vulkan.h>

namespace Shroom {
    
    namespace {
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            vk::DebugUtilsMessageTypeFlagsEXT messageType,
            const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        ) {
            String severity;
            if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose) 
                severity = "VERBOSE";
            else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo)
                severity = "INFO";
            else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning)
                severity = "WARNING";
            else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eError)
                severity = "ERROR";

            String type;
            if (messageType & vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral)
                type += "GENERAL";
            if (messageType & vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation)
                type += "VALIDATION";
            if (messageType & vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance)
                type += "PERFORMANCE";

            std::ostringstream message;
            message << "[VULKAN][" << severity << "][" << type << "]\n"
                    << "Message: " << pCallbackData->pMessage << "\n";

            if (pCallbackData->objectCount > 0) {
                message << "Objects:\n";
                for (uint32 i = 0; i < pCallbackData->objectCount; ++i) {
                    const auto& obj = pCallbackData->pObjects[i];
                    message << "  - Type: "
                            << vk::to_string(static_cast<vk::ObjectType>(obj.objectType))
                            << ", Handle: " << obj.objectHandle
                            << ", Name: " << (obj.pObjectName ? obj.pObjectName : "Unnamed")
                            << "\n";
                }
            }

            if (pCallbackData->cmdBufLabelCount > 0) {
                message << "Command buffer labels:\n";
                for (uint32 i = 0; i < pCallbackData->cmdBufLabelCount; ++i) {
                    message << "  - " << pCallbackData->pCmdBufLabels[i].pLabelName << "\n";
                }
            }

            if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eError) {
                SCORE_ERROR(message.str().c_str());
            } else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
                SCORE_WARN(message.str().c_str());
            } else {
                SCORE_TRACE(message.str().c_str());
            }

            return VK_FALSE;
        }
    }
        
    void VulkanRendererAPI::Init() {
        SCORE_INFO("Initializing Vulkan Renderer API...");

        auto vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(SDL_Vulkan_GetVkGetInstanceProcAddr());

        context.emplace(vkGetInstanceProcAddr);
        auto vulkanVersion = context->enumerateInstanceVersion();
        SCORE_TRACE("Vulkan {}.{}", VK_API_VERSION_MAJOR(vulkanVersion), VK_API_VERSION_MINOR(vulkanVersion));
    
        CreateInstance();
        CreateSurface();
        PickPhysicalDevice();
        PickQueueFamilies();
        CreateDevice();
        CreateCommandPool();
        InitFrames();

        RecreateSwapchain(
            Application::Get().GetWindow().GetWidth(),
            Application::Get().GetWindow().GetHeight()
        );
    }

    void VulkanRendererAPI::Shutdown() {
        _Device->waitIdle();
    }

    bool VulkanRendererAPI::BeginFrame() { 
        const VulkanFrame& frame = *_Frames[_FrameIndex];
        
        auto _ = _Device->waitForFences(*frame.Fence, VK_TRUE, UINT64_MAX);
        _Device->resetFences(*frame.Fence);

        auto[acquireResult,imageIndex] = _Swapchain->acquireNextImage(UINT64_MAX, frame.ImageAvailableSemaphore, nullptr);
        _CurrentSwapchainImageIndex = imageIndex;

        return true;
    }

    void VulkanRendererAPI::EndFrame() {
        const VulkanFrame& frame = *_Frames[_FrameIndex];
        
        frame.CommandBuffer.end();

        vk::SubmitInfo submitInfo{};
        submitInfo.setCommandBuffers(*frame.CommandBuffer);
        submitInfo.setWaitSemaphores(*frame.ImageAvailableSemaphore);
        submitInfo.setSignalSemaphores(*frame.RenderFinishedSemaphore);
        const vk::PipelineStageFlags waitStage = vk::PipelineStageFlagBits::eTransfer;
        submitInfo.setWaitDstStageMask(waitStage);

        _GraphicsQueue->submit(submitInfo, *frame.Fence);

        vk::PresentInfoKHR presentInfo{};
        presentInfo.setSwapchains(**_Swapchain);
        presentInfo.setImageIndices(_CurrentSwapchainImageIndex);
        presentInfo.setWaitSemaphores(*frame.RenderFinishedSemaphore);

        auto _ = _GraphicsQueue->presentKHR(presentInfo);

        _FrameIndex = (_FrameIndex + 1) % IN_FLIGHT_FRAME_COUNT;
    }
    
    void VulkanRendererAPI::Clear() {
        const VulkanFrame& frame = *_Frames[_FrameIndex];
        const auto& swapchainImage = _SwapchainImages[_CurrentSwapchainImageIndex];

        frame.CommandBuffer.reset();
        vk::CommandBufferBeginInfo beginInfo{};
        beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
        frame.CommandBuffer.begin(beginInfo);

        constexpr vk::ClearColorValue clearColor{1.0f, 0.0f, 0.0f, 1.0f};

        const vk::ImageMemoryBarrier2 barrier(
            vk::PipelineStageFlagBits2::eTransfer,
            vk::AccessFlagBits2::eMemoryRead,
            vk::PipelineStageFlagBits2::eTransfer,
            vk::AccessFlagBits2::eTransferWrite,
            vk::ImageLayout::eUndefined,
            vk::ImageLayout::eTransferDstOptimal,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            swapchainImage,
            vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}
        );
        vk::DependencyInfo dependencyInfo{};
        dependencyInfo.setImageMemoryBarriers(barrier);
        frame.CommandBuffer.pipelineBarrier2(dependencyInfo);

        frame.CommandBuffer.clearColorImage(
            swapchainImage, 
            vk::ImageLayout::eTransferDstOptimal, 
            clearColor,
            vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}
        );
        
        const vk::ImageMemoryBarrier2 barrier2(
            vk::PipelineStageFlagBits2::eTransfer,
            vk::AccessFlagBits2::eTransferWrite,
            vk::PipelineStageFlagBits2::eTransfer,
            vk::AccessFlagBits2::eMemoryRead,
            vk::ImageLayout::eTransferDstOptimal,
            vk::ImageLayout::ePresentSrcKHR,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            swapchainImage,
            vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}
        );
        vk::DependencyInfo dependencyInfo2{};
        dependencyInfo2.setImageMemoryBarriers(barrier2);
        frame.CommandBuffer.pipelineBarrier2(dependencyInfo2);
    }

    void VulkanRendererAPI::RecreateSwapchain(uint32 width, uint32 height) {
        // prevent minimized window
        if (width == 0 || height == 0) return; 

        vk::SurfaceCapabilitiesKHR surfaceCapabilities = _PhysicalDevice->getSurfaceCapabilitiesKHR(*_Surface);

        // get extent
        if (surfaceCapabilities.currentExtent != UINT32_MAX) {
            _SwapchainExtent = surfaceCapabilities.currentExtent;
        } else {
            _SwapchainExtent = vk::Extent2D{
                std::clamp(width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width),
                std::clamp(height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height)
            };
        }

        // get image count
        uint32 imageCount = surfaceCapabilities.minImageCount + 1;
        if (surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceCapabilities.maxImageCount)
            imageCount = surfaceCapabilities.maxImageCount;

        // pick surface format
        auto formats = _PhysicalDevice->getSurfaceFormatsKHR(*_Surface);
        _ImageFormat = formats[0];
        for (const auto& format: formats) {
            if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                _ImageFormat = format;
                break;
            }
        }

        vk::SwapchainCreateInfoKHR createInfo{};
        createInfo.surface = *_Surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = _ImageFormat.format;
        createInfo.imageColorSpace = _ImageFormat.colorSpace;
        createInfo.imageExtent = _SwapchainExtent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst;
        createInfo.imageSharingMode = vk::SharingMode::eExclusive;
        createInfo.preTransform = surfaceCapabilities.currentTransform;
        createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
        createInfo.presentMode = vk::PresentModeKHR::eFifo;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = _Swapchain ? **_Swapchain : VK_NULL_HANDLE;

        vk::raii::SwapchainKHR newSwapchain(*_Device, createInfo);

        _Swapchain = std::move(newSwapchain);
        _SwapchainImages = _Swapchain->getImages();
    }

    void VulkanRendererAPI::CreateInstance() {
        SCORE_TRACE("Creating Vulkan instance...");

        // extensions
        uint32 sdlExtensionCount;
        auto sdlExtensions = SDL_Vulkan_GetInstanceExtensions(&sdlExtensionCount);
        
        std::vector<const char*> extensions(sdlExtensions, sdlExtensions+sdlExtensionCount);

        // layers
        std::vector<const char*> layers;
        if (VULKAN_ENABLE_VALIDATION) {
            layers.push_back("VK_LAYER_KHRONOS_validation");
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        // app info
        vk::ApplicationInfo appInfo{};
        appInfo.setApiVersion(VULKAN_VERSION);

        // debug messenger
        vk::DebugUtilsMessengerCreateInfoEXT debugInfo{};
        if (VULKAN_ENABLE_VALIDATION) {
            debugInfo = {
                {},
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
                DebugCallback
            };
        }
        
        // instance create info
        vk::InstanceCreateInfo createInfo{};
        createInfo.pApplicationInfo = &appInfo;
        
        createInfo.enabledLayerCount = (uint32)layers.size();
        createInfo.ppEnabledLayerNames = layers.data();

        createInfo.enabledExtensionCount = (uint32)extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (VULKAN_ENABLE_VALIDATION)
            createInfo.pNext = &debugInfo;

        _Instance.emplace(*context, createInfo);
        
        if (VULKAN_ENABLE_VALIDATION)
            _Debug.emplace(*_Instance, debugInfo);
    }

    void VulkanRendererAPI::CreateSurface() {
        SCORE_TRACE("Creating Vulkan surface...");

        SDL_Window* window = (SDL_Window*)Application::Get().GetWindow().GetNativeWindow();

        VkSurfaceKHR surface;
        if (!SDL_Vulkan_CreateSurface(window, **_Instance, nullptr, &surface))
            SCORE_ASSERT(false, "Failed to create Vulkan surface!");
        
        _Surface.emplace(*_Instance, surface);
    }

    void VulkanRendererAPI::PickPhysicalDevice() {
        const auto physicalDevices = _Instance->enumeratePhysicalDevices();
        SCORE_ASSERT(!physicalDevices.empty(), "No Vulkan devices found!");

        _PhysicalDevice.emplace(*_Instance, *physicalDevices.front());
        const auto rawDeviceName = _PhysicalDevice->getProperties().deviceName;
        String deviceName(rawDeviceName.data(), strlen(rawDeviceName));
        SCORE_TRACE("Picked Vulkan device: {0}", deviceName);
    }

    void VulkanRendererAPI::PickQueueFamilies() {
        auto queueFamilies = _PhysicalDevice->getQueueFamilyProperties();

        bool found = false;

        for (uint32_t i = 0; i < queueFamilies.size(); ++i) {
            auto queueFlag = queueFamilies[i].queueFlags;
            bool graphics = bool(queueFlag & vk::QueueFlagBits::eGraphics);
            bool present  = _PhysicalDevice->getSurfaceSupportKHR(i, *_Surface);

            if (graphics && present) {
                _GraphicsQueueFamilyIndex = i;
                _PresentQueueFamilyIndex  = i;
                found = true;
                break;
            }
        }

        SCORE_ASSERT(found, "Failed to find a graphics+present queue family");
    }

    void VulkanRendererAPI::CreateDevice() {
        // graphics queue
        vk::DeviceQueueCreateInfo graphicsInfo{};
        graphicsInfo.queueFamilyIndex = _GraphicsQueueFamilyIndex;
        std::array<float32, 1> queuePriorities{1.0f};
        graphicsInfo.queueCount = 1;
        graphicsInfo.setQueuePriorities(queuePriorities);

        // device
        vk::DeviceCreateInfo createInfo{};
        
        std::array queueInfos{graphicsInfo};
        createInfo.setQueueCreateInfos(queueInfos);
        
        std::array<const char* const, 1> enabledExtensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
        createInfo.setPEnabledExtensionNames(enabledExtensions);

        // enable sync2
        vk::PhysicalDeviceSynchronization2Features sync2Features{};
        sync2Features.setSynchronization2(VK_TRUE);
        createInfo.setPNext(&sync2Features);
        
        _Device.emplace(*_PhysicalDevice, createInfo);

        _GraphicsQueue.emplace(*_Device, _GraphicsQueueFamilyIndex, 0);
    }

    void VulkanRendererAPI::CreateCommandPool() {
        vk::CommandPoolCreateInfo createInfo{};
        createInfo.queueFamilyIndex = _GraphicsQueueFamilyIndex;
        createInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
        
        _CommandPool.emplace(*_Device, createInfo);
    }

    void VulkanRendererAPI::InitFrames() {
        // allocate command buffers
        vk::CommandBufferAllocateInfo allocateInfo{};
        allocateInfo.commandPool = *_CommandPool;
        allocateInfo.level = vk::CommandBufferLevel::ePrimary;
        allocateInfo.commandBufferCount = IN_FLIGHT_FRAME_COUNT;
        auto commandBuffers = _Device->allocateCommandBuffers(allocateInfo);

        vk::FenceCreateInfo fenceCreateInfo{};
        fenceCreateInfo.flags = vk::FenceCreateFlagBits::eSignaled;

        vk::SemaphoreCreateInfo semaphoreCreateInfo{};

        for (uint32 i = 0; i < IN_FLIGHT_FRAME_COUNT; i++) {

            _Frames[i].emplace(
                std::move(commandBuffers[i]),
                vk::raii::Semaphore(*_Device, semaphoreCreateInfo),
                vk::raii::Semaphore(*_Device, semaphoreCreateInfo),
                vk::raii::Fence(*_Device, fenceCreateInfo)
            );
        }
    }

} // namespace Shroom
