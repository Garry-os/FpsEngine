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

private:
    Window* window;
};
