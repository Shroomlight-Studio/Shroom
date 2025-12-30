#include "Renderer.h"

namespace Shroom {

    Owned<RendererAPI> Renderer::_RAPI;
    bool Renderer::_FrameSkipped = false;

   void Renderer::Init() {
        SCORE_INFO("Initializing Renderer...");
        RendererAPISpecification spec{};
        spec.EnableValidation = true;
        _RAPI = RendererAPI::Create(spec);
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

    void Renderer::RecreateSwapchain(uint32 width, uint32 height) {
        _RAPI->RecreateSwapchain(width, height);
    }

} // namespace Shroom
