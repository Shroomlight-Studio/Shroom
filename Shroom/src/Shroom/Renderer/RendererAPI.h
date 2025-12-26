#pragma once

namespace Shroom {
    
    class RendererAPI {
    public:
        enum class API {
            None = 0,
            Vulkan
        };

        inline static API GetAPI() { return _API; }

    private:
        static API _API;
    };

} // namespace Shroom

