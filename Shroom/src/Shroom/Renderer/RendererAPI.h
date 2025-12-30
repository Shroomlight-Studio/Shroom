#pragma once

#include "Shroom/Core/Core.h"

namespace Shroom {

    class RendererAPI {
    public:
        enum class API {
            None = 0,
            Vulkan
        };

    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void Shutdown() = 0;

        virtual bool BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual void Clear() = 0;
        virtual void RecreateSwapchain(uint32 width, uint32 height) = 0;

        inline static API GetAPI() { return _API; }

        static Owned<RendererAPI> Create();

    private:
        static API _API;
    };

} // namespace Shroom

