cmake_minimum_required(VERSION 3.10)
project(TApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add source files
set(SOURCES
        # Window sources
        src/Window/Window.cpp

        # Application sources
        src/Application/Application.cpp

        src/main.cpp
)

# Add header files
set(HEADERS
        # Utils headers
        include/Utils/Memory/PoolAllocator/PoolAllocator.h
        include/Utils/Memory/PoolAllocator/PoolAllocator.tpp

        include/Utils/Memory/Singleton/Singleton.h
        include/Utils/Memory/Singleton/Singleton.tpp

        include/Utils/Logging/Logging.h

        # Layers headers
        include/Layers/Layer/Layer.h

        include/Layers/LayerStack/LayerStack.h
        include/Layers/LayerStack/LayerStack.tpp

        # Window headers
        include/Window/Window.h
        include/Window/WindowEvents.h
        include/Window/WindowSettings.h

        # Event headers
        include/Events/Event/Event.h
        include/Events/Event/Event.tpp

        include/Events/EventListener/EventListener.h

        include/Events/EventDispatcher/EventDispatcher.h
        include/Events/EventDispatcher/EventDispatcher.tpp

        include/Events/EventManager/EventManager.h
        include/Events/EventManager/EventManager.tpp

        # Input headers
        include/Input/InputEvents.h

        # Application headers
        include/Application/Application.h

        include/TApp.h

)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Set up GLAD
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Set up GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

# Set up ImGui
file(GLOB IMGUI_SOURCES
        external/imgui/*.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC external/imgui
)

# Includes and sources
include_directories(include)
add_executable(TApp ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(TApp
        ${OPENGL_gl_LIBRARY}
        glad
        glfw
        ImGui
)

if(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
endif()