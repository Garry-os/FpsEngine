#pragma once
#include "window.h"
#include <memory>
#include "resources/resourceManager.h"

class Mesh;
class Shader;
class Camera;

struct GLFWwindow;

class Engine {
public:
    Engine();
    ~Engine();

    bool initialize();

    void handleInputs();
    void update();
    inline bool windowShouldClose() const { return window->shouldClose(); }
    inline Window& getWindowNative() const { return *window; }
    inline Camera& getCamera() const { return *camera; }

private:
    // Application's window
    std::unique_ptr<Window> window;

    std::unique_ptr<Shader> shader;
    MeshHandle meshHandle;

    // Resource manager
    std::unique_ptr<ResourceMananager> rsManager;

    // Game's camera
    std::unique_ptr<Camera> camera;

    float deltaTime;

    static void mouseCallback(GLFWwindow*, double xPos, double yPos);
};
