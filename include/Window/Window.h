#ifndef WINDOW_H
#define WINDOW_H

#include <imgui.h>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Window/WindowSettings.h"
#include "Layers/LayerStack/LayerStack.h"
#include "Events/EventManager/EventManager.h"
#include "Window/WindowEvents.h"
#include "Input/InputEvents.h"

#define TAPP_WINDOW_LAYER_STACK_SIZE 10

namespace TApp {
    class Window {
    public:
        Window(WindowSettings&& windowSettings, std::shared_ptr<EventManager> eventManager);
        ~Window();

        bool init();

        void makeContextCurrent();

        void makeImGuiContextCurrent();

        void update(float deltaTime);

        void render();


        // Getters
        GLFWwindow* getGLFWWindow() const;

        const WindowSettings& getWindowSettings() const;

        bool shouldClose() const;

        LayerStack& getLayerStack();

        bool isKeyPressed(int key) const;
        bool isMouseButtonPressed(int button) const;

        double getMouseX() const;
        double getMouseY() const;
        void getMouseXY(double* x, double* y) const;

        double getTime() const;

        // Setters
        void setVSync(bool enabled);

        void setTitle(const std::string& title);

        void setTime(double time);

        static void setClearColour(float r, float g, float b, float a);

        void setWindowShouldClose(bool shouldClose);

        void setFrameBufferSizeCallback(GLFWframebuffersizefun callback);

        void setKeyCallback(GLFWkeyfun callback);

        void setMouseButtonCallback(GLFWmousebuttonfun callback);

    private:
        void clearColorBuffer();

        void clearDepthBuffer();

        void swapBuffers();

        void pollEvents();

        void setCallbacks();

    private:
        GLFWwindow* glfwWindow;

        WindowSettings windowSettings;

        std::shared_ptr<EventManager> eventManager;

        LayerStack layerStack;

        ImGuiContext* imguiContext;

    private:
        static bool gladInitialised;
        static bool glfwInitialised;
        static bool imguiInitialised;
    };
}

#endif //WINDOW_H
