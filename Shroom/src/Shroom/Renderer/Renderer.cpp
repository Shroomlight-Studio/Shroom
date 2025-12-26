#include "Renderer.h"

namespace Shroom {

    Owned<RendererAPI> Renderer::_RAPI;
    bool Renderer::_FrameSkipped = false;

   void Renderer::Init() {
        SCORE_INFO("Initializing Renderer...");
        RendererAPISpecification spec{};
        _RAPI = RendererAPI::Create(spec);
        _RAPI->Init();
    }

    void Renderer::Shutdown() {
        _RAPI->Shutdown();
        _RAPI.reset();
    }

    void Renderer::BeginFrame() {
        
    }

    void Renderer::EndFrame() {
        if (_FrameSkipped) return;
        
    }


} // namespace Shroom
