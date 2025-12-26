#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Core/Clock.h"
#include "Shroom/Core/Window.h"
#include "Shroom/Core/LayerStack.h"
#include "Shroom/Events/ApplicationEvents.h"

namespace Shroom {

    struct ApplicationSpecification {
        String Title = "Shroom Application";
        uint32 Width = 1280;
        uint32 Height = 720;
        String WorkingDirectory = "./";
    };

    class Application {
    public:
        Application(const ApplicationSpecification& spec);
        virtual ~Application();

        void Run();
        void Close();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() { return *_Instance; }

    private:
        bool OnWindowClosed(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        Owned<Window> _Window;
        bool _Running = false;

        LayerStack _LayerStack;
        
        Clock _Clock;
        float64 _LastFrameTime = 0.0;

        static Application* _Instance;
    };

    // Implemented by CLIENT
    Application* CreateApplication();

}
