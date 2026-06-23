#include "window.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "engine.h"

Window::Window()
    :window(nullptr), width(0), height(0) {}

Window::~Window() {
    // Destroy the window instance
    glfwDestroyWindow(window);
}

/*
 * Create a window.
 * Returns false if failed, true if succeed.
 * If fullScreen is true, p_width and p_height will be ignored.
 */
bool Window::createWindow(bool fullScreen, int p_width, int p_height, const std::string& title, Engine* enginePtr) {
    // Enable borders
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Create a GLFWwindow
    if (fullScreen)
    {
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(), nullptr, nullptr);
    }
    else
        window = glfwCreateWindow(p_width, p_height, title.c_str(), nullptr, nullptr);

    if (!window) {
        return false;
    }

    this->width = p_width;
    this->height = p_height;

    // Store window instance
    glfwSetWindowUserPointer(window, enginePtr);

    // Make GLFW context
    glfwMakeContextCurrent(window);
    // Set resize callback
    glfwSetFramebufferSizeCallback(window, fb_resize_callback);

    return true;
}

void Window::fb_resize_callback(GLFWwindow* window, int p_width, int p_height) {
    glViewport(0, 0, p_width, p_height);
    
    // Update window's width & height
    Engine* handler = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (handler) {
        handler->getWindowNative().width = p_width;
        handler->getWindowNative().height = p_height;
    }
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}
