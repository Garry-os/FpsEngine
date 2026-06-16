#pragma once
#include <string>

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    bool createWindow(int p_width, int p_height, const std::string& title);
    inline GLFWwindow* getNativeWindow() const { return window; }
    bool shouldClose() const;

    void clear(float r, float g, float b, float a);
    void swapBuffers();

private:
    static void fb_resize_callback(GLFWwindow*, int p_width, int p_height);

    GLFWwindow* window;
    int width, height;
};
