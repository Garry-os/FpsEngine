#include "engine/engine.h"

int main() {
    // Create and initialize engine
    Engine* engine = new Engine();
    if (!engine->initialize()) {
        delete engine;
        return -1;
    }

    // Game loop
    while (!engine->windowShouldClose()) {
        engine->handleInputs();

        engine->update();
    }

    delete engine;

    return 0;
}
