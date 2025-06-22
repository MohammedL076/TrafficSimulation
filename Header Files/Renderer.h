// Renderer.h
#pragma once
#include "Streetlight.h"
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Renderer {
public:
    void init();
    void beginDraw(const std::vector<Streetlight>& lights);
    void endDraw();
    void setViewMatrix(const glm::mat4& view);

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
