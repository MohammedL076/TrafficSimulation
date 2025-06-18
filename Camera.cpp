#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera()
    : position(0, 10, 40), up(0, 1, 0), speed(10.0f),
    moveForward(false), moveBackward(false), moveLeft(false), moveRight(false),
    yaw(-90.0f), pitch(0.0f)
{
    front = glm::vec3(0, 0, -1);
}


void Camera::update(float deltaTime) {
    glm::vec3 moveDir(0.0f);
    
    glm::vec3 flatFront = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

    if (moveForward) moveDir += flatFront;
    if (moveBackward) moveDir -= flatFront;
    if (moveLeft) moveDir -= glm::normalize(glm::cross(flatFront, up));
    if (moveRight) moveDir += glm::normalize(glm::cross(flatFront, up));

    if (glm::length(moveDir) > 0.01f)
        position += glm::normalize(moveDir) * speed * deltaTime;
}


void Camera::processKeyboard(int key, int action) {
    bool pressed = action != GLFW_RELEASE;
    if (key == GLFW_KEY_W) moveForward = pressed;
    if (key == GLFW_KEY_S) moveBackward = pressed;
    if (key == GLFW_KEY_A) moveLeft = pressed;
    if (key == GLFW_KEY_D) moveRight = pressed;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processMouse(float xpos, float ypos)
{
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(dir);
}


