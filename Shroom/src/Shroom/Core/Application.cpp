#include "Application.h"

#include "Shroom/Renderer/Renderer.h"

namespace Shroom {

    Application* Application::_Instance = nullptr;

    Application::Application(const ApplicationSpecification& spec) {
        SCORE_INFO("Creating application...");

        SCORE_ASSERT(!_Instance, "Application already exists!");
        _Instance = this;

        if (!spec.WorkingDirectory.empty())
            std::filesystem::current_path(spec.WorkingDirectory);

        // create a window
        _Window = Window::Create(WindowSpecification(spec.Title, spec.Width, spec.Height));
        _Window->SetEventCallbackFunction(SHROOM_BIND_EVENT_FN(Application::OnEvent));

        // init subsystems
        Renderer::Init();

        _Running = true;
    }

    Application::~Application() {
        // shutdown subsystems
        Renderer::Shutdown();

        // destroy the window
        _Window.reset();
    }
    
    void Application::Run() {
        while (_Running) {
            const float64 time = _Clock.Elapsed();
            const float64 deltatime = time - _LastFrameTime;
            _LastFrameTime = time;

            Renderer::BeginFrame();
            Renderer::Clear();

            for (Layer* l : _LayerStack)
                l->OnUpdate(deltatime);

            Renderer::EndFrame();

            _Window->OnUpdate();
        }
    }

    void Application::Close() {
        _Running = false;
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(SHROOM_BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(SHROOM_BIND_EVENT_FN(Application::OnWindowResize));

        for (Layer* l : _LayerStack)
            l->OnEvent(e);
    }

    void Application::PushLayer(Layer* layer) {
        _LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay) {
        _LayerStack.PushOverlay(overlay);
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        Close();
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
        Renderer::RecreateSwapchain(e.GetWidth(), e.GetHeight());
        return false;
    }

} // namespace Shroom


