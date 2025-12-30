#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Renderer/RendererAPI.h"

#include "Platform/Vulkan/VulkanFactory.h"
#include "Platform/Vulkan/VulkanFrame.h"

namespace Shroom {

    constexpr bool VULKAN_ENABLE_VALIDATION = true;
    constexpr uint32 IN_FLIGHT_FRAME_COUNT = 2;

    class VulkanRendererAPI : public RendererAPI {    
    public:
        VulkanRendererAPI() = default;
        virtual ~VulkanRendererAPI() = default;

        virtual void Init() override;
        virtual void Shutdown() override;

        virtual bool BeginFrame() override;
        virtual void EndFrame() override;

        virtual void Clear() override;
        virtual void RecreateSwapchain(uint32 width, uint32 height) override;

    private:
        void CreateInstance();
        void CreateSurface();
        void PickPhysicalDevice();
        void PickQueueFamilies();
        void CreateDevice();
        void CreateCommandPool();
        void InitFrames();

    private:
        std::optional<vk::raii::Context> context{};
       
        std::optional<vk::raii::Instance> _Instance{};
        std::optional<vk::raii::DebugUtilsMessengerEXT> _Debug = nullptr;

        std::optional<vk::raii::SurfaceKHR> _Surface{};

        std::optional<vk::raii::PhysicalDevice> _PhysicalDevice{};
        std::optional<vk::raii::Device> _Device{};

        uint32 _GraphicsQueueFamilyIndex;
        std::optional<vk::raii::Queue> _GraphicsQueue{};

        uint32 _PresentQueueFamilyIndex;

        std::optional<vk::raii::CommandPool> _CommandPool{};
        std::array<std::optional<VulkanFrame>, IN_FLIGHT_FRAME_COUNT> _Frames{};
        uint32 _FrameIndex = 0;

        std::optional<vk::raii::SwapchainKHR> _Swapchain{};
        std::vector<vk::Image> _SwapchainImages{};
        vk::Extent2D _SwapchainExtent{};
        vk::SurfaceFormatKHR _ImageFormat{};
        uint32 _CurrentSwapchainImageIndex;
    };
    
} // namespace Shroom

