#ifndef WINDOWSETTINGS_H
#define WINDOWSETTINGS_H

#include <string>

namespace TApp {
    struct WindowSettings {
        WindowSettings(unsigned int width = 1280, unsigned int height = 720, std::string title = "", bool vsync = false)
            : width(width), height(height), title(std::move(title)), vsync(vsync) {}
        unsigned int width, height;
        std::string title;
        bool vsync;
    };
}

#endif //WINDOWSETTINGS_H
