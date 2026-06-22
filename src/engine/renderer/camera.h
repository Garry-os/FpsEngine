#pragma once
#include <glm/glm.hpp>

enum class CameraDirection {
    Forward,
    Backward,
    Left,
    Right
};

class Camera {
public:
    Camera(glm::vec3 cameraPos, float fov, float width, float height, float nearPlane, float farPlane);
    ~Camera() = default;

    void setPosition(glm::vec3 newPos);

    glm::mat4 getCameraMatrix() const;

    void processKeyboard(float dt, CameraDirection dir);
    void processMouse(float xOffset, float yOffset);

    float cameraSpeed = 2.5f;
    float mouseSens = 0.02f;

    float yaw         = -90.0f;
    float pitch       =  0.0f;
    float speed       =  2.5f;
    float sensitivity =  0.1f;
    float zoom        =  45.0f;

private:
    glm::vec3 m_cameraPos;
    
    glm::mat4 m_projection;
    glm::mat4 m_view;

    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    
    void updateCameraVectors();
    void updateMatrix();
};

