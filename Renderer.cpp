#include "Renderer.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace tigl;

void Renderer::init() {
    tigl::init();

    // Orthografisch voor nu, later perspectief
    projectionMatrix = glm::perspective(glm::radians(45.0f), 1400.0f / 800.0f, 0.1f, 1000.0f);
    viewMatrix = glm::lookAt(
        glm::vec3(0, 20, 40),   // camera positie
        glm::vec3(0, 0, 0),     // kijkrichting
        glm::vec3(0, 1, 0)      // up vector
    );
}

void Renderer::beginDraw() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setProjectionMatrix(projectionMatrix);
    shader->setViewMatrix(viewMatrix);
}

void Renderer::endDraw() {
    // niks nodig voor nu
}

void Renderer::setViewMatrix(const glm::mat4& view) {
	viewMatrix = view;
}
