#pragma once
#include "window.h"

class Engine {
public:
    Engine();
    ~Engine();

    bool initialize();

    void handleInputs();
    void update();
    inline bool windowShouldClose() const { return window->shouldClose(); }
    inline Window& getWindowNative() const { return *window; }

private:
    Window* window;
};
