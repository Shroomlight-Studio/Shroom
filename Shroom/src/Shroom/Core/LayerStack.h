#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Core/Layer.h"

namespace Shroom {

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        void PushOverlay(Layer* overlay);
        void PopOverLay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return _Layers.begin(); }
        std::vector<Layer*>::iterator end() { return _Layers.end(); }

    private:
        std::vector<Layer*> _Layers;
        uint32 _LayerInsertIndex = 0;
    };

} // namespace Shroom
