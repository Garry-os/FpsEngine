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

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }

private:
    static void fb_resize_callback(GLFWwindow* window, int p_width, int p_height);

    GLFWwindow* window;
    int width, height;
};
