#pragma once

#include "Shroom/Core/Core.h"

namespace Shroom {

    class Event;

    class Layer {
    public:
        Layer(const String& name = "Layer") : _DebugName(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float64 deltatime) {}
        virtual void OnEvent(Event& e) {}

        inline const String& GetName() const { return _DebugName; }

    private:
        String _DebugName;
    };

} // namespace Shroom
