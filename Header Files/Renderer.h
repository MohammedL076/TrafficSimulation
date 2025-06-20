#pragma once

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Renderer {
public:
    void init();
    void beginDraw();
    void endDraw();

    void setViewMatrix(const glm::mat4& view);

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
