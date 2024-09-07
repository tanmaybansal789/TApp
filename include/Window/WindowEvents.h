#ifndef WINDOWEVENTS_H
#define WINDOWEVENTS_H

namespace TApp {
    class Window;

    namespace InternalEvents {

        class WindowResizeEvent : public Event {
        public:
            WindowResizeEvent(unsigned int width=0, unsigned int height=0, TApp::Window* window=nullptr)
                : width(width), height(height), window(window), Event(makeEventScopes(WindowScope)) {}

            // Getters
            unsigned int getWidth() const { return width; }
            unsigned int getHeight() const { return height; }
            Window* getWindow() const { return window; }

        private:
            unsigned int width, height;
            Window* window;
        };
    }
}


#endif //WINDOWEVENTS_H
