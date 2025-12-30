#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Renderer/RendererAPI.h"

#include "Platform/Vulkan/VulkanFactory.h"

namespace Shroom {

    class VulkanRendererAPI : public RendererAPI {
    public:
        VulkanRendererAPI(const RendererAPISpecification& spec);
        virtual ~VulkanRendererAPI() = default;

        virtual void Init() override;
        virtual void Shutdown() override;

        virtual bool BeginFrame() override;
        virtual void EndFrame() override;

        virtual void RecreateSwapchain(uint32 width, uint32 height) override;

    private:
        void CreateInstance();
        void CreateSurface();
        void PickPhysicalDevice();
        void PickQueueFamilies();
        void CreateDevice();
        void CreateCommandPool();
        void AllocateCommandBuffers();
        void InitSyncObjects();

    private:
        RendererAPISpecification _Spec;

        std::optional<vk::raii::Context> context{};
       
        std::optional<vk::raii::Instance> _Instance{};
        std::optional<vk::raii::DebugUtilsMessengerEXT> _Debug{nullptr};

        std::optional<vk::raii::SurfaceKHR> _Surface{};

        std::optional<vk::raii::PhysicalDevice> _PhysicalDevice{};
        std::optional<vk::raii::Device> _Device{};

        uint32 _GraphicsQueueFamilyIndex;
        std::optional<vk::raii::Queue> _GraphicsQueue{};

        uint32 _PresentQueueFamilyIndex;

        std::optional<vk::raii::CommandPool> _CommandPool{};
        std::vector<vk::raii::CommandBuffer> _CommandBuffers{};

        std::vector<vk::raii::Fence> _Fences{};
        std::vector<vk::raii::Semaphore> _ImageAvailableSemaphores{};
        std::vector<vk::raii::Semaphore> _RenderFinishedSemaphores{};

        std::optional<vk::raii::SwapchainKHR> _Swapchain{};
        std::vector<vk::Image> _SwapchainImages{};
        vk::Extent2D _SwapchainExtent{};
        vk::SurfaceFormatKHR _ImageFormat{};
        uint32 _CurrentSwapchainImageIndex;
    };
    
} // namespace Shroom

