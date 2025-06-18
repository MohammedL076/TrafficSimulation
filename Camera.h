#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();
    float yaw, pitch;
    float lastX = 700, lastY = 400;
    bool firstMouse = true;

    void update(float deltaTime);
    void processKeyboard(int key, int action);
	void processMouse(float xpos, float ypos);

    glm::mat4 getViewMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float speed;
    bool moveForward, moveBackward, moveLeft, moveRight;
};
