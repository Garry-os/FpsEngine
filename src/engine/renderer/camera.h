#pragma once
#include <glm/glm.hpp>

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera {
public:
    Camera(glm::vec3 cameraPos, float fov, float width, float height, float nearPlane, float farPlane);
    ~Camera() = default;

    void setPosition(glm::vec3 newPos);

    glm::mat4 getCameraMatrix() const;

private:
    glm::vec3 m_cameraPos;
    
    glm::mat4 m_projection;
    glm::mat4 m_view;

    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    
    void updateCameraVectors();
};

