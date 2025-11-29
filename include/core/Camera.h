//
// Created by htlix on 2025/10/31.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f,
           float pitch = 0.0f);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
           float yaw, float pitch);

    glm::mat4 getViewMatrix();

    void processKeyboard(Camera_Movement direction, double deltaTime);
    void processMouseMovement(double xOffset, double yOffset);
    void setYaw(float yaw);
    void setPitch(float pitch);

    float getPitch();
    float getYaw();

    // 反转视角
    void invertCamera();

    glm::vec3 getPosition() const { return this->m_position; }
    void setPosition(glm::vec3 position) { this->m_position = position; }

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float movementSpeed;
    float mouseSensitivity;
    float yaw;
    float pitch;
    void updateCameraVectors();
};

#endif // CAMERA_H