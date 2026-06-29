#include "engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/vertexBufferLayout.h"
#include "renderer/shader.h"
#include "renderer/camera.h"
#include "scene/transform.h"

// 1280x720 resolution
constexpr int w_width = 1280;
constexpr int w_height = 720;

static float lastTime = 0.f;
static bool firstMouse = true;

static float lastMouseX = 0.f;
static float lastMouseY = 0.f;

Engine::Engine() {
    deltaTime = 0.f;
    window = std::make_unique<Window>();
}

Engine::~Engine() {
    glfwTerminate();
}

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
uint32_t indices[] = {  // note that we start from 0!
    0, 1, 3,            // first triangle
    1, 2, 3             // second triangle
};

Transform transforms[] = {
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 2.0f, 2.0f, 2.0f},
    {5.0f, 3.0f, 1.0f, 1.0f},
    {1.0f, 2.0f, 7.0f, 1.0f},
};

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
    if (!window->createWindow(true, w_width, w_height, "FPS shooter", this)) {
        std::cerr << "Failed to create window" << std::endl;
        return false;
    }

    // Load OpenGL function pointres
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load OpenGL (GLAD) function pointers" << std::endl;
        return false;
    }
    glfwSetCursorPosCallback(window->getNativeWindow(), mouseCallback);
    glfwSetInputMode(window->getNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Vsync
    glfwSwapInterval(1);

    // Initialize engine's internals
    rsManager = std::make_unique<ResourceManager>();

    // Construct the mesh
    VertexBufferLayout layout = VertexBufferLayout();
    layout.addElement(DataType::Float, 3, false);

    MeshInfo meshInfo;
    meshInfo.vertices = vertices;
    meshInfo.vertexSizeInBytes = sizeof(vertices);
    meshInfo.indices = indices;
    meshInfo.indexCount = sizeof(indices);
    meshInfo.layout = layout;

    meshHandle = rsManager->createMesh(meshInfo);
    shaderHandle = rsManager->loadShader("shaders/vert.glsl", "shaders/frag.glsl");

    camera = std::make_unique<Camera>(glm::vec3(0.f, 0.f, 1.5f), 45.f, window->getWidth(), window->getHeight(), 0.1f, 100.f);

    return true;
}

void Engine::handleInputs() {
    if (glfwGetKey(window->getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window->getNativeWindow(), 1);
    }

    // Camera input
    if (glfwGetKey(window->getNativeWindow(), GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(deltaTime, CameraDirection::Forward);
    if (glfwGetKey(window->getNativeWindow(), GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(deltaTime, CameraDirection::Backward);
    if (glfwGetKey(window->getNativeWindow(), GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(deltaTime, CameraDirection::Left);
    if (glfwGetKey(window->getNativeWindow(), GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(deltaTime, CameraDirection::Right);
}

void Engine::update() {
    // Calculate delta time
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastTime;
    lastTime = currentFrame;

    // Handle user inputs
    handleInputs();

    // Clear screen
    window->clear(0.f, 0.f, 0.f, 1.f);

    for (int i = 0; i < 4; i++)
    {
        Shader& shader = rsManager->getShader(shaderHandle);
        shader.bind();
        shader.setUniform4f("u_color", std::sin(glfwGetTime() * 5.0f), 0.5f, std::sin(glfwGetTime() * 2.0f), 1.0f);
        shader.setUniformMat4f("u_mvp", camera->getCameraMatrix() * transforms[i].getModelMatrix());
        rsManager->getMesh(meshHandle).draw();
    }

    // Swap buffers
    window->swapBuffers();

    // Poll events
    glfwPollEvents();
}
void Engine::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
    // Calculate the offset
    float x = static_cast<float>(xPos);
    float y = static_cast<float>(yPos);

    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    float xOffset = x - lastMouseX;
    float yOffset = y - lastMouseY;

    lastMouseX = x;
    lastMouseY = y;

    // Camera rotation
    Engine* handler = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (handler) {
        handler->getCamera().processMouse(xOffset, yOffset);
    }
}
