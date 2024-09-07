#include "Application/Application.h"

namespace TApp {
    Application::Application() : window(nullptr) {}

    void Application::init(WindowSettings&& settings) {
        eventManager = std::make_shared<EventManager>();
        window = new Window(std::move(settings), eventManager);
        window->init();

        onInit();
    }

    void Application::run(WindowSettings&& settings) {
        init(std::move(settings));

        while (!window->shouldClose()) {
            std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
            lastFrameTime = now;

            window->render();
            window->update(deltaTime);
            update(deltaTime);

        }

        shutdown();
    }

    void Application::shutdown() {
        delete window;

        glfwTerminate();

        onShutdown();
    }

    // Getters
    Window* Application::getWindow() const {
        return window;
    }

    const std::shared_ptr<EventManager>& Application::getEventManager() const {
        return eventManager;
    }
}