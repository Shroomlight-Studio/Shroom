#include "SDLWindow.h"

#include "Shroom/Events/ApplicationEvents.h"
#include "Shroom/Events/KeyEvents.h"
#include "Shroom/Events/MouseEvents.h"
#include "Shroom/Renderer/RendererAPI.h"

#include "Platform/SDL/SDLInputUtils.h"

namespace Shroom {

#if defined(SHROOM_PLATFORM_WINDOWS) || defined(SHROOM_PLATFORM_LINUX)
    Owned<Window> Window::Create(const WindowSpecification& spec) {
        return Own<SDLWindow>(spec);
    }
#endif

    SDLWindow::SDLWindow(const WindowSpecification &spec) {
        Init(spec);
    }

    SDLWindow::~SDLWindow() {
        Shutdown();
    }

    void SDLWindow::OnUpdate() {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            DispatchEvent(event);
    }

    void SDLWindow::Init(const WindowSpecification& spec) {
        _Data.Title = spec.Title;
        _Data.Width = spec.Width;
        _Data.Height = spec.Height;
        _Data.VSync = spec.VSync;

        SCORE_INFO("Creating SDL window {0} ({1}, {2})...", _Data.Title, _Data.Width, _Data.Height);
    
        if (!SDL_WasInit(SDL_INIT_VIDEO))
            SCORE_ASSERT(!SDL_Init(SDL_INIT_VIDEO), "Failed to initialize SDL3 subsystem.");
        
        SDL_WindowFlags flags = 0;
        flags |= spec.Resizable ? SDL_WINDOW_RESIZABLE : 0;

        if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
            flags |= SDL_WINDOW_VULKAN;

        _Handle = SDL_CreateWindow(
            _Data.Title.c_str(),
            _Data.Width, _Data.Height,
            flags
        );

        SCORE_ASSERT(_Handle, "Failed to create SDL Window!");
    }
    
    void SDLWindow::Shutdown() {
        SCORE_INFO("Destroying SDL window {0}...", _Data.Title);

        if (_Handle) {
            SDL_DestroyWindow(_Handle);
            _Handle = nullptr;
        }

        SDL_Quit();
    }
    
    void SDLWindow::DispatchEvent(const SDL_Event& event) {
        switch (event.type) {
        // -------------------------
        // Window Close
        // -------------------------
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                WindowCloseEvent e;
                _Data.EventCallback(e);
            }
        // -------------------------
        // Window Focus
        // -------------------------
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            {
                WindowFocusEvent e;
                _Data.EventCallback(e);
                break;
            }
        // -------------------------
        // Window Moved
        // -------------------------
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            {
                WindowLostFocusEvent e;
                _Data.EventCallback(e);
                break;
            }
        // -------------------------
        // Window Resize
        // -------------------------
        case SDL_EVENT_WINDOW_MAXIMIZED:
        case SDL_EVENT_WINDOW_RESIZED:
            {
                _Data.Width = event.window.data1;
                _Data.Height = event.window.data2;

                WindowResizeEvent e(_Data.Width, _Data.Height);
                _Data.EventCallback(e);
                break;
            }
        case SDL_EVENT_WINDOW_MINIMIZED:
            {
                WindowResizeEvent e(0, 0);
                _Data.EventCallback(e);
                break;
            }
        case SDL_EVENT_WINDOW_RESTORED:
            {
                WindowResizeEvent e(_Data.Width, _Data.Height);
                _Data.EventCallback(e);
                break;
            }
        // -------------------------
        // Keyboard Input
        // -------------------------
        case SDL_EVENT_KEY_DOWN:
            {
                KeyPressedEvent e(Utils::KeyCodeFromSDL(event.key.key), 0);
                _Data.EventCallback(e);
                break;
            }
        case SDL_EVENT_KEY_UP:
            {
                KeyReleasedEvent e(Utils::KeyCodeFromSDL(event.key.key));
                _Data.EventCallback(e);
                break;
            }
        // -------------------------
        // Mouse Buttons
        // -------------------------
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                MouseButtonPressedEvent e(Utils::MouseCodeFromSDL(event.button.button));
                _Data.EventCallback(e);
                break;
            }
        case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                MouseButtonReleasedEvent e(Utils::MouseCodeFromSDL(event.button.button));
                _Data.EventCallback(e);
                break;
            }
        // -------------------------
        // Mouse Mouvement
        // -------------------------
        case SDL_EVENT_MOUSE_MOTION:
            {
                MouseMovedEvent e(event.motion.x, event.motion.y);
                _Data.EventCallback(e);
                break;
            }
        // -------------------------
        // Mouse Wheel
        // -------------------------
        case SDL_EVENT_MOUSE_WHEEL:
            {
                MouseScrolledEvent e(event.wheel.x, event.wheel.y);
                _Data.EventCallback(e);
                break;
            }
        }
    }    

} // namespace Shroom
