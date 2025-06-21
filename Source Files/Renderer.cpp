#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

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



void Renderer::beginDraw() {

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setProjectionMatrix(projectionMatrix);
    shader->setViewMatrix(viewMatrix);

    shader->enableLighting(true);
    shader->setLightCount(1);
    shader->setLightDirectional(0, true);
    shader->setLightPosition(0, glm::vec3(-1.0f, -1.0f, -1.0f)); 
    shader->setLightAmbient(0, glm::vec3(0.1f));  
    shader->setLightDiffuse(0, glm::vec3(1.0f, 1.0f, 1.0f));   
    shader->setLightSpecular(0, glm::vec3(1.0f, 1.0f, 1.0f));  

    shader->setShinyness(128.0f); 

}

void Renderer::endDraw() {
}

void Renderer::setViewMatrix(const glm::mat4& view) {
	viewMatrix = view;
}
