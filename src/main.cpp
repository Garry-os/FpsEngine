#include "engine/engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/renderer/indexBuffer.h"
#include "engine/renderer/shader.h"
#include "engine/renderer/vertexBuffer.h"
#include "engine/renderer/vertexArray.h"
#include "engine/renderer/vertexBufferLayout.h"

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
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    VertexBuffer buffer = VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer ibo = IndexBuffer(indices, sizeof(indices));

    VertexBufferLayout layout = VertexBufferLayout();
    layout.addElement(DataType::Float, 3, false);

    VertexArray array = VertexArray();
    array.addVertexBuffer(buffer, layout);
    array.setIndexBuffer(ibo);

    Shader shader("shaders/vert.glsl", "shaders/frag.glsl");

    // Game loop
    while (!engine->windowShouldClose()) {
        engine->handleInputs();
 
        window.clear(0.f, 0.f, 0.f, 1.f);

        array.bind();
        shader.bind();
        ibo.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        window.swapBuffers();
        glfwPollEvents();

        // engine->update();
    }

    delete engine;

    return 0;
}
