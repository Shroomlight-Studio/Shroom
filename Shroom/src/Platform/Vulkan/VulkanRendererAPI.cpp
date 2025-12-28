#include "VulkanRendererAPI.h"

#include "Shroom/Core/Application.h"

#include <SDL3/SDL_vulkan.h>

namespace Shroom {
    
    namespace {
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            vk::DebugUtilsMessageSeverityFlagBitsEXT,
            vk::DebugUtilsMessageTypeFlagsEXT,
            const vk::DebugUtilsMessengerCallbackDataEXT* data,
            void*
        ) {
            SCORE_ERROR("[VULKAN] {}", data->pMessage);
            return VK_FALSE;
        }
    }

    VulkanRendererAPI::VulkanRendererAPI(const RendererAPISpecification& spec) : _Spec(spec) {}
        
    void VulkanRendererAPI::Init() {
        SCORE_INFO("Initializing Vulkan Renderer API...");

        auto vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(SDL_Vulkan_GetVkGetInstanceProcAddr());

        context.emplace(vkGetInstanceProcAddr);
        auto vulkanVersion = context->enumerateInstanceVersion();
        SCORE_TRACE("Vulkan {}.{}", VK_API_VERSION_MAJOR(vulkanVersion), VK_API_VERSION_MINOR(vulkanVersion));
    
        CreateInstance();
        CreateSurface();
        PickPhysicalDevice();
        CreateDevice();
        CreateCommandPool();
        AllocateCommandBuffers();
        InitSyncObjects();
    }

    void VulkanRendererAPI::Shutdown() {
        _Device.reset();
        _PhysicalDevice.reset();
        _Surface.reset();
        _Instance.reset();
    }

    void VulkanRendererAPI::CreateInstance() {
        SCORE_TRACE("Creating Vulkan instance...");

        // extensions
        uint32 extensionCount;
        auto extensions = SDL_Vulkan_GetInstanceExtensions(&extensionCount);

        // layers
        std::vector<const char*> layers;
        if (_Spec.EnableValidation)
            layers.push_back("VK_LAYER_KHRONOS_validation");

        // app info
        vk::ApplicationInfo appInfo{};
        appInfo.setApiVersion(VULKAN_VERSION);
        
        // instance create info
        vk::InstanceCreateInfo createInfo{};
        createInfo.pApplicationInfo = &appInfo;
        
        createInfo.enabledLayerCount = (uint32)layers.size();
        createInfo.ppEnabledLayerNames = layers.data();

        createInfo.enabledExtensionCount = extensionCount;
        createInfo.ppEnabledExtensionNames = extensions;

        _Instance.emplace(*context, createInfo);

        if (_Spec.EnableValidation) {
            vk::DebugUtilsMessengerCreateInfoEXT dbg{
                {},
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
                DebugCallback
            };

            _Debug.emplace(*_Instance, *dbg);
        }
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

        // for now we hardcode those values
        _GraphicsQueueFamilyIndex = 0;
        _PresentQueueFamilyIndex = 0;
    }

    void VulkanRendererAPI::CreateDevice() {
        // graphics queue
        vk::DeviceQueueCreateInfo graphicsInfo{};
        graphicsInfo.queueFamilyIndex = _GraphicsQueueFamilyIndex;
        std::array<float32, 1> queuePriorities{1.0f};
        graphicsInfo.setQueuePriorities(queuePriorities);

        // device
        vk::DeviceCreateInfo createInfo{};
        
        std::array queueInfos{graphicsInfo};
        createInfo.setQueueCreateInfos(queueInfos);
        
        std::array<const char* const, 1> enabledExtensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
        createInfo.setPpEnabledExtensionNames(enabledExtensions.data());

        _Device.emplace(*_PhysicalDevice, createInfo);

        _GraphicsQueue.emplace(*_Device, _GraphicsQueueFamilyIndex, 0);
    }

    void VulkanRendererAPI::CreateCommandPool() {
        vk::CommandPoolCreateInfo createInfo{};
        createInfo.queueFamilyIndex = _GraphicsQueueFamilyIndex;
        createInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
        
        _CommandPool.emplace(*_Device, createInfo);
    }

    void VulkanRendererAPI::AllocateCommandBuffers() {
        vk::CommandBufferAllocateInfo allocateInfo{};
        allocateInfo.commandPool = *_CommandPool;
        allocateInfo.commandBufferCount = 1;

        _CommandBuffers = _Device->allocateCommandBuffers(allocateInfo);
    }

    void VulkanRendererAPI::InitSyncObjects() {
        vk::FenceCreateInfo createInfo{};
        createInfo.flags = vk::FenceCreateFlagBits::eSignaled;

        _Fence.emplace(*_Device, createInfo);
    }

} // namespace Shroom
