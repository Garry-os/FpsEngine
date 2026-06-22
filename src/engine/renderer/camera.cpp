#include "camera.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(glm::vec3 cameraPos, float fov, float width, float height, float nearPlane, float farPlane)
    :m_cameraPos(cameraPos)
{
    // Calculate the projection matrix
    m_projection = glm::perspective(glm::radians(fov), (float)width / (float)height, nearPlane, farPlane);

    // Set the vector directions
    m_front = glm::vec3(0.f, 0.f, -1.f);
    m_worldUp = glm::vec3(0.f, 1.f, 0.f);

    updateCameraVectors();
    m_view = glm::lookAt(cameraPos, cameraPos + m_front, m_up);
}

void Camera::updateCameraVectors() {
    // Update new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
    front.y = sin(glm::radians(PITCH));
    front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
    m_front = glm::normalize(front);
    // Update right & up vectors
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

// Get projection * view matrix
glm::mat4 Camera::getCameraMatrix() const {
    return m_projection * m_view;
}

void Camera::setPosition(glm::vec3 newPos) {
    m_cameraPos = newPos;
}

