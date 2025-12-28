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

    private:
        void CreateInstance();
        void CreateSurface();
        void PickPhysicalDevice();
        void CreateDevice();

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
    };
    
} // namespace Shroom

