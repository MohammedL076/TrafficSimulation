#include "Car.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace tigl;

Car::Car(const glm::vec3& position)
    : position(position) {
}

void Car::update(float deltaTime)
{
    // Simpele beweging in de z-richting
    position.z -= deltaTime * speed;
}

void Car::draw()
{
    shader->enableColor(true);
    shader->setModelMatrix(glm::translate(glm::mat4(1.0f), position));

    begin(GL_QUADS);
    addVertex(Vertex::PC(glm::vec3(-1, 0, -2), glm::vec4(0, 0, 1, 1))); // blauw
    addVertex(Vertex::PC(glm::vec3(1, 0, -2), glm::vec4(0, 0, 1, 1)));
    addVertex(Vertex::PC(glm::vec3(1, 0, 2), glm::vec4(0, 0, 1, 1)));
    addVertex(Vertex::PC(glm::vec3(-1, 0, 2), glm::vec4(0, 0, 1, 1)));
    end();
}
