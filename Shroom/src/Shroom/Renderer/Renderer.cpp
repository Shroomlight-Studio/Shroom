#include "Renderer.h"

namespace Shroom {

    Owned<RendererAPI> Renderer::_RAPI;
    bool Renderer::_FrameSkipped = false;

   void Renderer::Init() {
        SCORE_INFO("Initializing Renderer...");
        _RAPI = RendererAPI::Create();
        _RAPI->Init();
    }

    void Renderer::Shutdown() {
        _RAPI->Shutdown();
        _RAPI.reset();
    }

    void Renderer::BeginFrame() {
        _FrameSkipped = !_RAPI->BeginFrame();
    }

    void Renderer::EndFrame() {
        if (_FrameSkipped) return;
        _RAPI->EndFrame();
    }

    void Renderer::Clear() {
        if (_FrameSkipped) return;
        _RAPI->Clear();
    }

    void Renderer::RecreateSwapchain(uint32 width, uint32 height)
    {
        _RAPI->RecreateSwapchain(width, height);
    }

} // namespace Shroom
