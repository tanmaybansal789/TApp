#ifndef LAYERSTACK_TPP
#define LAYERSTACK_TPP

#define TAPP_CHECK_LAYER_VS_OVERLAY
#define TAPP_CHECK_LAYER_EXISTS

namespace TApp {
    LayerStack::LayerStack(size_t poolSize) : layerAllocator(poolSize) {}

    // Layers
    template <LayerType T, typename... Args>
    LayerId LayerStack::addLayer(Args&&... args) {
        Layer* layer = layerAllocator.allocate<T>(std::forward<Args>(args)...);
        LayerId id = (freedIds.empty()) ? nextId++ : freedIds.front();
        if (!freedIds.empty()) freedIds.pop();
        layers.push_back(layer);
        idToPos[id] = layers.size() - 1;
        layer->onAttach(id);
        return id;
    }

    LayerId LayerStack::getLayerId(Layer* layer) {
        auto it = std::find(layers.begin(), layers.end(), layer);
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (it == layers.end()) {
            return NULL_LAYER_ID;
        }
#endif
        return std::distance(layers.begin(), it);
    }

    Layer* LayerStack::getLayer(LayerId id) {
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (idToPos.find(id) == idToPos.end()) {
            return nullptr;
        }
#endif
        return layers[idToPos[id]];
    }

    template<LayerType T>
    T* LayerStack::getLayerAs(LayerId id) {
        return dynamic_cast<T*>(getLayer(id));
    }

    bool LayerStack::removeLayer(LayerId id) {
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (idToPos.find(id) == idToPos.end()) {
            return false;
        }
#endif
        size_t pos = idToPos[id];
        layers[pos]->onDetach();
        layerAllocator.deallocate(layers[pos]);
        layers.erase(layers.begin() + pos);
        idToPos.erase(id);
        freedIds.push(id);
        for (auto& [key, value] : idToPos) {
            if (value > pos) {
                --value;
            }
        }
        return true;
    }

    bool LayerStack::removeLayer(Layer* layer) {
        auto it = std::find(layers.begin(), layers.end(), layer);
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (it == layers.end()) {
            return false;
        }
#endif
        size_t pos = std::distance(layers.begin(), it);
        LayerId id = std::find_if(idToPos.begin(), idToPos.end(), [pos](const auto& pair) { return pair.second == pos; })->first;
        return removeLayer(id);
    }

    size_t LayerStack::layerSize() {
        return nextId;
    }

    bool LayerStack::layerEmpty() {
        return nextId == 0;
    }

    // Overlays
    template <LayerType T, typename... Args>
    LayerId LayerStack::addOverlay(Args&&... args) {
        Layer* overlay = layerAllocator.allocate<T>(std::forward<Args>(args)...);
        LayerId id = (freedIds.empty()) ? nextId++ : freedIds.front();
        if (!freedIds.empty()) freedIds.pop();
        layers.push_back(overlay);
        idToPos[id] = layers.size() - 1;
        overlay->onAttach(id);
        return id;
    }

    LayerId LayerStack::getOverlayId(Layer* overlay) {
        auto it = std::find(layers.begin(), layers.end(), overlay);
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (it == layers.end()) {
            return NULL_LAYER_ID;
        }
#endif
        return std::distance(layers.begin(), it);
    }

    Layer* LayerStack::getOverlay(LayerId id) {
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (idToPos.find(id) == idToPos.end()) {
            return nullptr;
        }
#endif
        return layers[idToPos[id]];
    }

    template<LayerType T>
    T* LayerStack::getOverlayAs(LayerId id) {
        return dynamic_cast<T*>(getOverlay(id));
    }

    bool LayerStack::removeOverlay(LayerId id) {
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (idToPos.find(id) == idToPos.end()) {
            return false;
        }
#endif
        size_t pos = idToPos[id];
        layers[pos]->onDetach();
        layerAllocator.deallocate(layers[pos]);
        layers.erase(layers.begin() + pos);
        idToPos.erase(id);
        freedIds.push(id);
        for (auto& [key, value] : idToPos) {
            if (value > pos) {
                --value;
            }
        }
        return true;
    }

    bool LayerStack::removeOverlay(Layer* overlay) {
        auto it = std::find(layers.begin(), layers.end(), overlay);
#ifdef TAPP_CHECK_LAYER_EXISTS
        if (it == layers.end()) {
            return false;
        }
#endif
        size_t pos = std::distance(layers.begin(), it);
        LayerId id = std::find_if(idToPos.begin(), idToPos.end(), [pos](const auto& pair) { return pair.second == pos; })->first;
        return removeOverlay(id);
    }

    size_t LayerStack::overlaySize() {
        return layers.size() - nextId;
    }

    bool LayerStack::overlayEmpty() {
        return layers.size() == nextId;
    }

    // Both
    size_t LayerStack::size() {
        return layers.size();
    }

    bool LayerStack::empty() {
        return layers.empty();
    }



    void LayerStack::onUpdate(float deltaTime) {
        for (Layer* layer : layers) {
            layer->onUpdate(deltaTime);
        }
    }

    void LayerStack::onRender() {
        for (Layer* layer : layers) {
            layer->onRender();
        }
    }
}

#endif //LAYERSTACK_TPP
