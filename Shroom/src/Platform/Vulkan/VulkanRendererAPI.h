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

    private:
        RendererAPISpecification _Spec;

       std::optional<vk::raii::Context> context{};
       
        std::optional<vk::raii::Instance> _Instance;
        std::optional<vk::raii::DebugUtilsMessengerEXT> _Debug{nullptr};

        std::optional<vk::raii::SurfaceKHR> _Surface;
    };
    
} // namespace Shroom

