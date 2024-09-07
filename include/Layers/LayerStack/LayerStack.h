#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include <vector>
#include <queue>
#include <unordered_map>

#include "Layers/Layer/Layer.h"
#include "Utils/Memory/PoolAllocator/PoolAllocator.h"

namespace TApp {
    using LayerId = size_t;

    using LayerAllocator = PoolAllocator<Layer>;

    template <typename T>
    concept LayerType = std::is_base_of_v<Layer, T>;

    constexpr LayerId NULL_LAYER_ID = std::numeric_limits<LayerId>::max();

    class LayerStack {
    public:
        inline explicit LayerStack(size_t poolSize);

        // Layers
        template <LayerType T, typename... Args>
        LayerId addLayer(Args&&... args);
        inline LayerId getLayerId(Layer* layer);
        inline Layer* getLayer(LayerId id);

        template <LayerType T>
        T* getLayerAs(LayerId id);

        inline bool removeLayer(LayerId id);
        inline bool removeLayer(Layer* layer);

        inline size_t layerSize();
        inline bool layerEmpty();

        // Overlays
        template <LayerType T, typename... Args>
        LayerId addOverlay(Args&&... args);
        inline LayerId getOverlayId(Layer* overlay);
        inline Layer* getOverlay(LayerId id);

        template <LayerType T>
        T* getOverlayAs(LayerId id);

        inline bool removeOverlay(LayerId id);
        inline bool removeOverlay(Layer* overlay);

        inline size_t overlaySize();
        inline bool overlayEmpty();

        // Both
        inline size_t size();
        inline bool empty();

        inline void onUpdate(float deltaTime);
        inline void onRender();

    private:
        LayerId nextId = 0;
        std::vector<Layer*> layers;
        std::unordered_map<LayerId, size_t> idToPos;
        std::queue<LayerId> freedIds;

        LayerAllocator layerAllocator;
    };
}

#include "Layers/LayerStack/LayerStack.tpp"

#endif //LAYERSTACK_H
