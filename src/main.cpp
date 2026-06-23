#include "engine/engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

int main() {
    // Create and initialize engine
    auto engine = std::make_unique<Engine>();
    if (!engine->initialize()) {
        return -1;
    }

    // Game loop
    while (!engine->windowShouldClose()) {
        engine->handleInputs();
 
        engine->update();
    }

    return 0;
}
