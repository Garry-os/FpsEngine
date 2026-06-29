#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform {
    glm::vec3 position; // Position
    glm::vec3 scale; // Scale
    glm::vec3 rotation; // Rotation

    Transform(glm::vec3 position, float scale)
        :position(position), scale(scale) {}

    Transform(glm::vec3 position, glm::vec3 scale)
        :position(position), scale(scale) {}

    Transform(float x, float y, float z, float scale)
        :position(x, y, z), scale(scale) {}

    Transform(float x, float y, float z, glm::vec3 scale)
        :position(x, y, z), scale(scale) {}

    glm::mat4 getModelMatrix() {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        // Translate
        modelMatrix = glm::translate(modelMatrix, position);
        // Rotate (YXZ order)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        // Scale
        modelMatrix = glm::scale(modelMatrix, scale);

        return modelMatrix;
    }
};
