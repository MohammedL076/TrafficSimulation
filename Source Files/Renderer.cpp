#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace tigl;

void Renderer::init() {
    tigl::init();

    projectionMatrix = glm::perspective(glm::radians(45.0f), 1400.0f / 800.0f, 0.1f, 1000.0f);
    viewMatrix = glm::lookAt(
        glm::vec3(0, 20, 40),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
}



void Renderer::beginDraw(const std::vector<Streetlight>& lights) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setProjectionMatrix(projectionMatrix);
    shader->setViewMatrix(viewMatrix);

    shader->enableLighting(true);   
    shader->setLightCount((int)lights.size());  


    shader->enableLighting(true);
    shader->setLightCount((int)lights.size());

    for (int i = 0; i < lights.size(); ++i) {
        shader->setLightPosition(i, lights[i].position);
        shader->setLightAmbient(i, lights[i].color * 0.1f);
        shader->setLightDiffuse(i, lights[i].color);
        shader->setLightSpecular(i, glm::vec3(1.0f));
        shader->setLightDirectional(i, false); 
    }

    shader->setShinyness(128.0f);
}

void Renderer::endDraw() {
}

void Renderer::setViewMatrix(const glm::mat4& view) {
	viewMatrix = view;
}
