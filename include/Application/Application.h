#ifndef APPLICATION_H
#define APPLICATION_H

#include <chrono>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "TApp.h"

namespace TApp {
    class Application {
    public:
        Application();

        void run(WindowSettings&& settings);

        // Getters
        Window* getWindow() const;
        const std::shared_ptr<EventManager>& getEventManager() const;

    protected:
        virtual void onInit() {}
        virtual void update(float deltaTime) {}
        virtual void onShutdown() {}

    protected:
        Window* window;
        std::shared_ptr<EventManager> eventManager;

    private:
        void init(WindowSettings&& settings);

        void shutdown();

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
    };
}

#endif //APPLICATION_H
