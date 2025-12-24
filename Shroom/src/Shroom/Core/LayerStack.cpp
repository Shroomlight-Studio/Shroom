#include "LayerStack.h"

namespace Shroom {

    LayerStack::~LayerStack() {
        for (Layer* layer : _Layers)
            delete layer;
        _Layers.clear();
    }

    void LayerStack::PushLayer(Layer* layer) {
        _Layers.emplace(begin() + _LayerInsertIndex, layer);
        _LayerInsertIndex++;
    }

    void LayerStack::PopLayer(Layer* layer) {
        std::vector<Layer*>::iterator it = std::find(begin(), end() + _LayerInsertIndex, layer);
        if (it == end()) return;
        _Layers.erase(it);
        _LayerInsertIndex--;
    }

    void LayerStack::PushOverlay(Layer* overlay) {
        _Layers.emplace_back(overlay);
    }

    void LayerStack::PopOverLay(Layer* overlay) {
        std::vector<Layer*>::iterator it = std::find(begin() + _LayerInsertIndex, end(), overlay);
        if (it == end()) return;
        _Layers.erase(it);
    }

} // namespace Shroom
