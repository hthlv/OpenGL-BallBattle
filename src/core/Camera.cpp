//
// Created by htlix on 2025/10/31.
//

#include "core/Camera.h"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_position(position),
      m_worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(2.5f),
      mouseSensitivity(0.1f) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch)
    : m_position(glm::vec3(posX, posY, posZ)), m_up(glm::vec3(upX, upY, upZ)),
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)), yaw(yaw), pitch(pitch),
      movementSpeed(2.5f), mouseSensitivity(0.1f) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(Camera_Movement direction, double deltaTime) {
    float velocity = deltaTime * movementSpeed;
    switch (direction) {
    case FORWARD:
        m_position += m_front * velocity;
        break;
    case BACKWARD:
        m_position -= m_front * velocity;
        break;
    case LEFT:
        m_position -= m_right * velocity;
        break;
    case RIGHT:
        m_position += m_right * velocity;
        break;
    }
}

void Camera::processMouseMovement(double xOffset, double yOffset) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

void Camera::setYaw(float yaw) {
    this->yaw = yaw;
    updateCameraVectors();
}

void Camera::setPitch(float pitch) {
    this->pitch = pitch;
    updateCameraVectors();
}

float Camera::getPitch() { return pitch; }

float Camera::getYaw() { return yaw; }

void Camera::invertCamera() {
    yaw += 180.0f;
    pitch = -pitch;

    updateCameraVectors();

    if (yaw > 360.0f)
        yaw -= 360.0f;
    if (yaw < -360.0f)
        yaw += 360.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 tempFront;
    tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tempFront.y = sin(glm::radians(pitch));
    tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_front = glm::normalize(tempFront);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
