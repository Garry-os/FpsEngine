#include "camera.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(glm::vec3 cameraPos, float fov, float width, float height, float nearPlane, float farPlane)
    :m_cameraPos(cameraPos)
{
    // Calculate the projection matrix
    m_projection = glm::perspective(glm::radians(fov), (float)width / (float)height, nearPlane, farPlane);
    m_view = glm::mat4(1.f);

    // Set the vector directions
    m_front = glm::vec3(0.f, 0.f, -1.f);
    m_worldUp = glm::vec3(0.f, 1.f, 0.f);

    updateCameraVectors();
    updateMatrix();
}

void Camera::updateCameraVectors() {
    // Update new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_front = glm::normalize(front);
    // Update right & up vectors
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

// Process keyboard inputs
void Camera::processKeyboard(float dt, CameraDirection dir) {
    float velocity = dt * cameraSpeed;
    switch (dir) {
        case CameraDirection::Forward: m_cameraPos += m_front * velocity; break;
        case CameraDirection::Backward: m_cameraPos -= m_front * velocity; break;
        case CameraDirection::Left: m_cameraPos -= m_right * velocity; break;
        case CameraDirection::Right: m_cameraPos += m_right * velocity; break;
    };
    updateMatrix();
}

// Process mouse inputs
void Camera::processMouse(float xOffset, float yOffset) {
    xOffset *= mouseSens;
    yOffset *= mouseSens;

    yaw += xOffset;
    pitch -= yOffset;

    // Constrain pitch
    pitch = glm::clamp(pitch, -89.f, 89.f); // -90 to 90 degree
    updateCameraVectors();
    updateMatrix();
}

// Get projection * view matrix
glm::mat4 Camera::getCameraMatrix() const {
    return m_projection * m_view;
}

void Camera::setPosition(glm::vec3 newPos) {
    m_cameraPos = newPos;
}

void Camera::updateMatrix() {
    m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_front, m_up);
}

void Camera::updateWindow(float fov, float newWidth, float newHeight, float nearPlane, float farPlane) {
    m_projection = glm::perspective(glm::radians(fov), (float)newWidth / (float)newHeight, nearPlane, farPlane);
}

