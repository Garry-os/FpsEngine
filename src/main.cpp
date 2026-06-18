#include "engine/engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/renderer/shader.h"
#include "engine/renderer/mesh.h"

int main() {
    // Create and initialize engine
    Engine* engine = new Engine();
    if (!engine->initialize()) {
        delete engine;
        return -1;
    }

    Window& window = engine->getWindowNative();

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    uint32_t indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    VertexBufferLayout layout = VertexBufferLayout();
    layout.addElement(DataType::Float, 3, false);

    Mesh quad = Mesh(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(uint32_t), layout);

    Shader shader("shaders/vert.glsl", "shaders/frag.glsl");

    // Game loop
    while (!engine->windowShouldClose()) {
        engine->handleInputs();
 
        window.clear(0.f, 0.f, 0.f, 1.f);

        shader.bind();
        quad.draw();

        window.swapBuffers();
        glfwPollEvents();

        // engine->update();
    }

    delete engine;

    return 0;
}
