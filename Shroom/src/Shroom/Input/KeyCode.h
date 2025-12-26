#pragma once

#include "Shroom/Core/Types.h"

namespace Shroom {

    struct KeyCode {
        enum : int32 {
            UNKNOWN = -1,

            // Letters
            A = 0, B, C, D, E, F, G, H, I, J,
            K, L, M, N, O, P, Q, R, S, T,
            U, V, W, X, Y, Z,

            // Numbers
            D0, D1, D2, D3, D4, D5, D6, D7, D8, D9,

            // Function keys
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
            F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,

            // Control 
            Space, Enter, Backspace,
            Escape, Tab, Capslock,

            // Modifiers
            LeftShift, RightShift,
            LeftControl, RightControl,
            LeftAlt, RightAlt,
            LeftSuper, RightSuper,

            // Navigation
            Insert, Delete, Home, End, PageUp, PageDown,
            ArrowUp, ArrowDown, ArrowLeft, ArrowRight,

            // Numpad
            Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
            Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
            NumpadAdd, NumpadSubstract, NumpadMultiply, NumpadDivide, NumpadDecimal,

            // Symbols
            Semicolon, Equal, Comma, Minus, Period, Slash, Grave,
            LeftBracket, Backslash, RightBracket, Apostrophe,

            // System keys
            PrintScreen, ScrollLock, Pause, Menu,
        };
        int32 value;

        constexpr KeyCode(int32 v) : value(v) {}
        constexpr operator int32() const { return value; }
    };

} // namespace Shroom
