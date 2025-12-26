#pragma once

#include "Shroom/Core/Window.h"

#include <SDL3/SDL.h>

namespace Shroom {

    class SDLWindow : public Window {
    public:
        SDLWindow(const WindowSpecification& spec);
        virtual ~SDLWindow();

        virtual void OnUpdate() override;
        
        virtual uint32 GetWidth() const override { return _Data.Width; }
        virtual uint32 GetHeight() const override { return _Data.Height; }
        
        virtual void SetEventCallbackFunction(const EventCallbackFunction& function) override { _Data.EventCallback = function; }
        
        virtual void SetVSync(bool enabled) override { _Data.VSync = enabled; }
        virtual bool IsVSync() const override { return _Data.VSync; }
        
        virtual void* GetNativeWindow() const override { return _Handle; }

    private:
        void Init(const WindowSpecification& spec);
        void Shutdown();
        void DispatchEvent(const SDL_Event& event);

    private:
        struct Data {
            String Title = "Shroom SDL Window";
            uint32 Width = 1280;
            uint32 Height = 720;
            bool VSync = true;
            EventCallbackFunction EventCallback;
        };
        Data _Data;

        SDL_Window* _Handle = nullptr;
    };

} // namespace Shroom
