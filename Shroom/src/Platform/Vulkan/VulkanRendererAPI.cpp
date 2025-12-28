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
    }

    void VulkanRendererAPI::Shutdown() {
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
    }

} // namespace Shroom
