#pragma once

#include "Shroom/Core/Types.h"

namespace Shroom::Platform {

    static float64 GetAbsoluteTime() {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::duration<float64>>(now.time_since_epoch()).count();
    }

} // namespace Shroom::Platform
