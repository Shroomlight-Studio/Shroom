#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Renderer/RendererAPI.h"

namespace Shroom {

    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void BeginFrame();
        static void EndFrame();

        static void Clear();
        static void RecreateSwapchain(uint32 width, uint32 height);

        inline static RendererAPI& GetAPI() { return *_RAPI; }
        
    private:
        static Owned<RendererAPI> _RAPI;
        static bool _FrameSkipped;
    };
    
} // namespace Shroom
