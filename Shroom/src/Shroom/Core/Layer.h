#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Events/Event.h"

namespace Shroom {

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
