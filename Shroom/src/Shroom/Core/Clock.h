#pragma once

#include "Shroom/Utils/PlatformUtils.h"

namespace Shroom {

    class Clock {
    public:
        Clock() { Reset(); }
        ~Clock() = default;

        void Reset() { _StartTime = Platform::GetAbsoluteTime(); }

        float64 Elapsed() const { return Platform::GetAbsoluteTime() - _StartTime; }
        float64 ElapsedMillis() const { return Elapsed() * 1000.0; }

    private:
        float64 _StartTime;
    };

} // namespace Shroom
