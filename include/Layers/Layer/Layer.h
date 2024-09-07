#ifndef LAYER_H
#define LAYER_H

namespace TApp {
    using LayerId = size_t;

    class Layer {
        friend class LayerStack;
    public:
        virtual ~Layer() = default;
    private:
        virtual void onAttach(LayerId id) {}
        virtual void onDetach() {}

        virtual void onUpdate(float deltaTime) {}
        virtual void onRender() {}
    };
}

#endif //LAYER_H