#include "Window/Window.h"

namespace TApp {
    bool Window::gladInitialised = false;
    bool Window::glfwInitialised = false;
    bool Window::imguiInitialised = false;

    Window::Window(WindowSettings&& windowSettings, std::shared_ptr<EventManager> eventManager)
        : glfwWindow(nullptr), windowSettings(std::move(windowSettings)), eventManager(std::move(eventManager)), layerStack(TAPP_WINDOW_LAYER_STACK_SIZE), imguiContext(nullptr) {}

    Window::~Window() {
        if (imguiContext) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext(imguiContext);
        }

        if (glfwWindow) {
            glfwDestroyWindow(glfwWindow);
        }
    }

    bool Window::init() {
        if (!glfwInitialised) {
            if (!glfwInit()) {
                TAPP_ERROR("Failed to initialize GLFW");
                return false;
            }
            glfwInitialised = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        glfwWindow = glfwCreateWindow(windowSettings.width, windowSettings.height, windowSettings.title.c_str(), nullptr, nullptr);

        if (!glfwWindow) {
            TAPP_ERROR("Failed to create window");
            return false;
        }

        makeContextCurrent();

        if (!gladInitialised) {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                TAPP_ERROR("Failed to initialize GLAD");
                return false;
            }
            gladInitialised = true;
        }

        if (!imguiInitialised) {
            IMGUI_CHECKVERSION();
        }

        imguiContext = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsClassic();

        if (!imguiInitialised) {
            ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
            ImGui_ImplOpenGL3_Init("#version 330");
            imguiInitialised = true;
        }

        setCallbacks();

        int width, height;
        glfwGetFramebufferSize(glfwWindow, &width, &height);
        glViewport(0, 0, width, height);

        glEnable(GL_DEPTH_TEST);

        return true;
    }

    void Window::makeContextCurrent() {
        glfwMakeContextCurrent(glfwWindow);
    }

    void Window::makeImGuiContextCurrent() {
        ImGui::SetCurrentContext(imguiContext);
    }

    void Window::update(float deltaTime) {
        layerStack.onUpdate(deltaTime);

        pollEvents();
    }

    void Window::render() {
        clearColorBuffer();
        clearDepthBuffer();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        layerStack.onRender();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        swapBuffers();
    }

    // Getters
    GLFWwindow* Window::getGLFWWindow() const {
        return glfwWindow;
    }

    const WindowSettings& Window::getWindowSettings() const {
        return windowSettings;
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(glfwWindow);
    }

    LayerStack& Window::getLayerStack() {
        return layerStack;
    }

    bool Window::isKeyPressed(int key) const {
        return glfwGetKey(glfwWindow, key) == GLFW_PRESS;
    }

    bool Window::isMouseButtonPressed(int button) const {
        return glfwGetMouseButton(glfwWindow, button) == GLFW_PRESS;
    }

    double Window::getMouseX() const {
        double x, y;
        glfwGetCursorPos(glfwWindow, &x, &y);
        return x;
    }

    double Window::getMouseY() const {
        double x, y;
        glfwGetCursorPos(glfwWindow, &x, &y);
        return y;
    }

    void Window::getMouseXY(double* x, double* y) const {
        glfwGetCursorPos(glfwWindow, x, y);
    }

    double Window::getTime() const {
        return glfwGetTime();
    }

    // Setters
    void Window::setVSync(bool enabled) {
        windowSettings.vsync = enabled;
        glfwSwapInterval(enabled ? 1 : 0);
    }

    void Window::setTitle(const std::string& title) {
        windowSettings.title = title;
        glfwSetWindowTitle(glfwWindow, title.c_str());
    }

    void Window::setTime(double time) {
        glfwSetTime(time);
    }

    void Window::setClearColour(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void Window::setWindowShouldClose(bool shouldClose) {
        glfwSetWindowShouldClose(glfwWindow, shouldClose);
    }

    void Window::setFrameBufferSizeCallback(GLFWframebuffersizefun callback) {
        glfwSetFramebufferSizeCallback(glfwWindow, callback);
    }

    void Window::setKeyCallback(GLFWkeyfun callback) {
        glfwSetKeyCallback(glfwWindow, callback);
    }

    void Window::setMouseButtonCallback(GLFWmousebuttonfun callback) {
        glfwSetMouseButtonCallback(glfwWindow, callback);
    }

    void Window::clearColorBuffer() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::clearDepthBuffer() {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(glfwWindow);
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    void Window::setCallbacks() {
        glfwSetWindowUserPointer(glfwWindow, this);

        setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
            windowInstance->eventManager->dispatch<InternalEvents::KeyEvent>(key, scancode, action, mods);

            ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        });

        setMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
            auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
            windowInstance->eventManager->dispatch<InternalEvents::MouseButtonEvent>(button, action, mods);

            ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        });

        setFrameBufferSizeCallback([](GLFWwindow* window, int width, int height) {
            auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
            windowInstance->eventManager->dispatch<InternalEvents::WindowResizeEvent>(width, height, windowInstance);
        });

    }
}