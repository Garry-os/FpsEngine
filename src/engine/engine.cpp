#include "engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 1280x720 resolution
constexpr int w_width = 1280;
constexpr int w_height = 720;

Engine::Engine() {
    window = new Window();
}

Engine::~Engine() {
    delete window;

    glfwTerminate();
}

bool Engine::initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // OpenGL 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the window instance
    if (!window->createWindow(w_width, w_height, "FPS shooter")) {
        std::cerr << "Failed to create window" << std::endl;
        return false;
    }

    // Load OpenGL function pointres
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load OpenGL (GLAD) function pointers" << std::endl;
        return false;
    }

    return true;
}

void Engine::handleInputs() {

}

void Engine::update() {
    handleInputs();

    // Clear screen
    window->clear(0.f, 0.f, 0.f, 1.f);

    // Swap buffers
    window->swapBuffers();

    // Poll events
    glfwPollEvents();
}
