#pragma once

#include "Shroom/Core/Core.h"

namespace Shroom {

    struct RendererAPISpecification {
        bool EnableValidation = false;
        uint32 FramesInFlight = 2;
    };

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

        inline static API GetAPI() { return _API; }

        static Owned<RendererAPI> Create(const RendererAPISpecification& spec);

    private:
        static API _API;
    };

} // namespace Shroom

