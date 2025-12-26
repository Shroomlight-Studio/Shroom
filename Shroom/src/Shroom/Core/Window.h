#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Events/Event.h"

namespace Shroom {

    struct WindowSpecification {
        String Title = "Shroom Window";
        uint32 Width = 1280;
        uint32 Height = 1280;
        bool Resizable = true;
        bool VSync = true;

        WindowSpecification() = default;
        WindowSpecification(const String& title, uint32 width, uint32 height, bool resizable = true, bool vsync = true)
            : Title(title)
            , Width(width)
            , Height(height)
            , Resizable(resizable)
            , VSync(vsync)
            {}
    };

    class Window {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;
        
        virtual uint32 GetWidth() const = 0;
        virtual uint32 GetHeight() const = 0;
        
        virtual void SetEventCallbackFunction(const EventCallbackFunction& function) = 0;
        
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        
        virtual void* GetNativeWindow() const = 0;
        
        static Owned<Window>Create(const WindowSpecification& spec = WindowSpecification());
    };
    
} // namespace Shroom

