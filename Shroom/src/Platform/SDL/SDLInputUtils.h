#pragma once

#include "Shroom/Core/Log.h"
#include "Shroom/Input/KeyCode.h"
#include "Shroom/Input/MouseCode.h"

#include <SDL3/SDL.h>

namespace Shroom::Utils {

    // -------------------------
    // Key Mapping
    // -------------------------

    inline static SDL_Keycode KeyCodeToSDL(KeyCode code) {
        switch (code) {
        // Letters
        case KeyCode::A: return SDLK_A;
        case KeyCode::B: return SDLK_B;
        case KeyCode::C: return SDLK_C;
        case KeyCode::D: return SDLK_D;
        case KeyCode::E: return SDLK_E;
        case KeyCode::F: return SDLK_F;
        case KeyCode::G: return SDLK_G;
        case KeyCode::H: return SDLK_H;
        case KeyCode::I: return SDLK_I;
        case KeyCode::J: return SDLK_J;
        case KeyCode::K: return SDLK_K;
        case KeyCode::L: return SDLK_L;
        case KeyCode::M: return SDLK_M;
        case KeyCode::N: return SDLK_N;
        case KeyCode::O: return SDLK_O;
        case KeyCode::P: return SDLK_P;
        case KeyCode::Q: return SDLK_Q;
        case KeyCode::R: return SDLK_R;
        case KeyCode::S: return SDLK_S;
        case KeyCode::T: return SDLK_T;
        case KeyCode::U: return SDLK_U;
        case KeyCode::V: return SDLK_V;
        case KeyCode::W: return SDLK_W;
        case KeyCode::X: return SDLK_X;
        case KeyCode::Y: return SDLK_Y;
        case KeyCode::Z: return SDLK_Z;

        // Numbers
        case KeyCode::D0: return SDLK_0;
        case KeyCode::D1: return SDLK_1;
        case KeyCode::D2: return SDLK_2;
        case KeyCode::D3: return SDLK_3;
        case KeyCode::D4: return SDLK_4;
        case KeyCode::D5: return SDLK_5;
        case KeyCode::D6: return SDLK_6;
        case KeyCode::D7: return SDLK_7;
        case KeyCode::D8: return SDLK_8;
        case KeyCode::D9: return SDLK_9;

        // Function keys
        case KeyCode::F1: return SDLK_F1;
        case KeyCode::F2: return SDLK_F2;
        case KeyCode::F3: return SDLK_F3;
        case KeyCode::F4: return SDLK_F4;
        case KeyCode::F5: return SDLK_F5;
        case KeyCode::F6: return SDLK_F6;
        case KeyCode::F7: return SDLK_F7;
        case KeyCode::F8: return SDLK_F8;
        case KeyCode::F9: return SDLK_F9;
        case KeyCode::F10: return SDLK_F10;
        case KeyCode::F11: return SDLK_F11;
        case KeyCode::F12: return SDLK_F12;
        case KeyCode::F13: return SDLK_F13;
        case KeyCode::F14: return SDLK_F14;
        case KeyCode::F15: return SDLK_F15;
        case KeyCode::F16: return SDLK_F16;
        case KeyCode::F17: return SDLK_F17;
        case KeyCode::F18: return SDLK_F18;
        case KeyCode::F19: return SDLK_F19;
        case KeyCode::F20: return SDLK_F20;

        // Control
        case KeyCode::Space: return SDLK_SPACE;
        case KeyCode::Enter: return SDLK_RETURN;
        case KeyCode::Backspace: return SDLK_BACKSPACE;
        case KeyCode::Escape: return SDLK_ESCAPE;
        case KeyCode::Tab: return SDLK_TAB;
        case KeyCode::Capslock: return SDLK_CAPSLOCK;

        // Modifiers
        case KeyCode::LeftShift: return SDLK_LSHIFT;
        case KeyCode::RightShift: return SDLK_RSHIFT;
        case KeyCode::LeftControl: return SDLK_LCTRL;
        case KeyCode::RightControl: return SDLK_RCTRL;
        case KeyCode::LeftAlt: return SDLK_LALT;
        case KeyCode::RightAlt: return SDLK_RALT;
        case KeyCode::LeftSuper: return SDLK_LGUI;
        case KeyCode::RightSuper: return SDLK_RGUI;

        // Navigation
        case KeyCode::Insert: return SDLK_INSERT;
        case KeyCode::Delete: return SDLK_DELETE;
        case KeyCode::Home: return SDLK_HOME;
        case KeyCode::End: return SDLK_END;
        case KeyCode::PageUp: return SDLK_PAGEUP;
        case KeyCode::PageDown: return SDLK_PAGEDOWN;

        case KeyCode::ArrowUp: return SDLK_UP;
        case KeyCode::ArrowDown: return SDLK_DOWN;
        case KeyCode::ArrowLeft: return SDLK_LEFT;
        case KeyCode::ArrowRight: return SDLK_RIGHT;

        // Numpad
        case KeyCode::Numpad0: return SDLK_KP_0;
        case KeyCode::Numpad1: return SDLK_KP_1;
        case KeyCode::Numpad2: return SDLK_KP_2;
        case KeyCode::Numpad3: return SDLK_KP_3;
        case KeyCode::Numpad4: return SDLK_KP_4;
        case KeyCode::Numpad5: return SDLK_KP_5;
        case KeyCode::Numpad6: return SDLK_KP_6;
        case KeyCode::Numpad7: return SDLK_KP_7;
        case KeyCode::Numpad8: return SDLK_KP_8;
        case KeyCode::Numpad9: return SDLK_KP_9;
        case KeyCode::NumpadAdd: return SDLK_KP_PLUS;
        case KeyCode::NumpadSubstract: return SDLK_KP_MINUS;
        case KeyCode::NumpadMultiply: return SDLK_KP_MULTIPLY;
        case KeyCode::NumpadDivide: return SDLK_KP_DIVIDE;
        case KeyCode::NumpadDecimal: return SDLK_KP_PERIOD;

        // Symbols
        case KeyCode::Semicolon: return SDLK_SEMICOLON;
        case KeyCode::Equal: return SDLK_EQUALS;
        case KeyCode::Comma: return SDLK_COMMA;
        case KeyCode::Minus: return SDLK_MINUS;
        case KeyCode::Period: return SDLK_PERIOD;
        case KeyCode::Slash: return SDLK_SLASH;
        case KeyCode::Grave: return SDLK_GRAVE;
        case KeyCode::LeftBracket: return SDLK_LEFTBRACKET;
        case KeyCode::Backslash: return SDLK_BACKSLASH;
        case KeyCode::RightBracket: return SDLK_RIGHTBRACKET;
        case KeyCode::Apostrophe: return SDLK_APOSTROPHE;

        // System
        case KeyCode::PrintScreen: return SDLK_PRINTSCREEN;
        case KeyCode::ScrollLock: return SDLK_SCROLLLOCK;
        case KeyCode::Pause: return SDLK_PAUSE;
        case KeyCode::Menu: return SDLK_MENU;

        default: return SDLK_UNKNOWN;
        }
    }

    inline static KeyCode KeyCodeFromSDL(SDL_Keycode code) {
        switch (code) {
        // Letters
        case SDLK_A: return KeyCode::A;
        case SDLK_B: return KeyCode::B;
        case SDLK_C: return KeyCode::C;
        case SDLK_D: return KeyCode::D;
        case SDLK_E: return KeyCode::E;
        case SDLK_F: return KeyCode::F;
        case SDLK_G: return KeyCode::G;
        case SDLK_H: return KeyCode::H;
        case SDLK_I: return KeyCode::I;
        case SDLK_J: return KeyCode::J;
        case SDLK_K: return KeyCode::K;
        case SDLK_L: return KeyCode::L;
        case SDLK_M: return KeyCode::M;
        case SDLK_N: return KeyCode::N;
        case SDLK_O: return KeyCode::O;
        case SDLK_P: return KeyCode::P;
        case SDLK_Q: return KeyCode::Q;
        case SDLK_R: return KeyCode::R;
        case SDLK_S: return KeyCode::S;
        case SDLK_T: return KeyCode::T;
        case SDLK_U: return KeyCode::U;
        case SDLK_V: return KeyCode::V;
        case SDLK_W: return KeyCode::W;
        case SDLK_X: return KeyCode::X;
        case SDLK_Y: return KeyCode::Y;
        case SDLK_Z: return KeyCode::Z;

        // Numbers
        case SDLK_0: return KeyCode::D0;
        case SDLK_1: return KeyCode::D1;
        case SDLK_2: return KeyCode::D2;
        case SDLK_3: return KeyCode::D3;
        case SDLK_4: return KeyCode::D4;
        case SDLK_5: return KeyCode::D5;
        case SDLK_6: return KeyCode::D6;
        case SDLK_7: return KeyCode::D7;
        case SDLK_8: return KeyCode::D8;
        case SDLK_9: return KeyCode::D9;

        // Function keys
        case SDLK_F1: return KeyCode::F1;
        case SDLK_F2: return KeyCode::F2;
        case SDLK_F3: return KeyCode::F3;
        case SDLK_F4: return KeyCode::F4;
        case SDLK_F5: return KeyCode::F5;
        case SDLK_F6: return KeyCode::F6;
        case SDLK_F7: return KeyCode::F7;
        case SDLK_F8: return KeyCode::F8;
        case SDLK_F9: return KeyCode::F9;
        case SDLK_F10: return KeyCode::F10;
        case SDLK_F11: return KeyCode::F11;
        case SDLK_F12: return KeyCode::F12;
        case SDLK_F13: return KeyCode::F13;
        case SDLK_F14: return KeyCode::F14;
        case SDLK_F15: return KeyCode::F15;
        case SDLK_F16: return KeyCode::F16;
        case SDLK_F17: return KeyCode::F17;
        case SDLK_F18: return KeyCode::F18;
        case SDLK_F19: return KeyCode::F19;
        case SDLK_F20: return KeyCode::F20;

        // Control 
        case SDLK_SPACE: return KeyCode::Space;
        case SDLK_RETURN: return KeyCode::Enter;
        case SDLK_BACKSPACE: return KeyCode::Backspace;
        case SDLK_ESCAPE: return KeyCode::Escape;
        case SDLK_TAB: return KeyCode::Tab;
        case SDLK_CAPSLOCK: return KeyCode::Capslock;

        // Modifiers
        case SDLK_LSHIFT: return KeyCode::LeftShift;
        case SDLK_RSHIFT: return KeyCode::RightShift;
        case SDLK_LCTRL: return KeyCode::LeftControl;
        case SDLK_RCTRL: return KeyCode::RightControl;
        case SDLK_LALT: return KeyCode::LeftAlt;
        case SDLK_RALT: return KeyCode::RightAlt;
        case SDLK_LGUI: return KeyCode::LeftSuper;
        case SDLK_RGUI: return KeyCode::RightSuper;

        // Navigation
        case SDLK_INSERT: return KeyCode::Insert;
        case SDLK_DELETE: return KeyCode::Delete;
        case SDLK_HOME: return KeyCode::Home;
        case SDLK_END: return KeyCode::End;
        case SDLK_PAGEUP: return KeyCode::PageUp;
        case SDLK_PAGEDOWN: return KeyCode::PageDown;

        case SDLK_UP: return KeyCode::ArrowUp;
        case SDLK_DOWN: return KeyCode::ArrowDown;
        case SDLK_LEFT: return KeyCode::ArrowLeft;
        case SDLK_RIGHT: return KeyCode::ArrowRight;

        // Numpad
        case SDLK_KP_0: return KeyCode::Numpad0;
        case SDLK_KP_1: return KeyCode::Numpad1;
        case SDLK_KP_2: return KeyCode::Numpad2;
        case SDLK_KP_3: return KeyCode::Numpad3;
        case SDLK_KP_4: return KeyCode::Numpad4;
        case SDLK_KP_5: return KeyCode::Numpad5;
        case SDLK_KP_6: return KeyCode::Numpad6;
        case SDLK_KP_7: return KeyCode::Numpad7;
        case SDLK_KP_8: return KeyCode::Numpad8;
        case SDLK_KP_9: return KeyCode::Numpad9;
        case SDLK_KP_PLUS: return KeyCode::NumpadAdd;
        case SDLK_KP_MINUS: return KeyCode::NumpadSubstract;
        case SDLK_KP_DIVIDE: return KeyCode::NumpadDivide;
        case SDLK_KP_PERIOD: return KeyCode::NumpadDecimal;

        // Symbols
        case SDLK_SEMICOLON: return KeyCode::Semicolon;
        case SDLK_EQUALS: return KeyCode::Equal;
        case SDLK_COMMA: return KeyCode::Comma;
        case SDLK_MINUS: return KeyCode::Minus;
        case SDLK_PERIOD: return KeyCode::Period;
        case SDLK_SLASH: return KeyCode::Slash;
        case SDLK_GRAVE: return KeyCode::Grave;
        case SDLK_LEFTBRACKET: return KeyCode::LeftBracket;
        case SDLK_BACKSLASH: return KeyCode::Backslash;
        case SDLK_RIGHTBRACKET: return KeyCode::RightBracket;
        case SDLK_APOSTROPHE: return KeyCode::Apostrophe;

        // System keys
        case SDLK_PRINTSCREEN: return KeyCode::PrintScreen;
        case SDLK_SCROLLLOCK: return KeyCode::ScrollLock;
        case SDLK_PAUSE: return KeyCode::Pause;
        case SDLK_MENU: return KeyCode::Menu;

        default:
            SCORE_WARN("Unknown SDL keycode: {0}", (int32)code);
            return KeyCode::UNKNOWN;
        }
    }

    // -------------------------
    // Mouse Mapping
    // -------------------------

    inline static uint8 MouseCodeToSDL(MouseCode code) {
        switch (code) {
        case MouseCode::ButtonLeft: return SDL_BUTTON_LEFT;
        case MouseCode::ButtonRight: return SDL_BUTTON_RIGHT;
        case MouseCode::ButtonMiddle: return SDL_BUTTON_MIDDLE;
        case MouseCode::ButtonX1: return SDL_BUTTON_X1;
        case MouseCode::ButtonX2: return SDL_BUTTON_X2;
        default: return SDL_BUTTON_LEFT;
        }
    }

    inline static MouseCode MouseCodeFromSDL(uint8 code) {
        switch (code) {
        case SDL_BUTTON_LEFT: return MouseCode::ButtonLeft;
        case SDL_BUTTON_RIGHT: return MouseCode::ButtonRight;
        case SDL_BUTTON_MIDDLE: return MouseCode::ButtonMiddle;
        case SDL_BUTTON_X1: return MouseCode::ButtonX1;
        case SDL_BUTTON_X2: return MouseCode::ButtonX2;
        default:
            SCORE_WARN("Unknown SDL mouse code: {0}", code);
            return MouseCode::ButtonLeft;
        }
    }

} // namespace Shroom::Utils