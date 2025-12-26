#pragma once

#include "Shroom/Core/Types.h"

namespace Shroom {

    struct MouseCode {
        enum : int32 {
            ButtonLeft = 0,
            ButtonRight = 1,
            ButtonMiddle = 2,
            ButtonX1 = 3,  // typically "Back" button
            ButtonX2 = 4,  // typically "Forward" button

            ScrollUp = 5,
            ScrollDown = 6,
            ScrollLeft = 7,
            ScrollRight = 8,
        };
        int32 value;

        constexpr MouseCode(int32 v) : value(v) {}
        constexpr operator int32() const { return value; }
    };

} // namespace Shroom
