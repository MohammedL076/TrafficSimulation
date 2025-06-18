#include "Road.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

using tigl::Vertex;
using namespace tigl;

Road::Road(const glm::vec3& position, const glm::vec2& size)
    : position(position), size(size) {
}

void Road::update(float) {
    // niks nodig voor nu
}

void Road::draw() {
    shader->setModelMatrix(glm::translate(glm::mat4(1.0f), position));

    begin(GL_QUADS);
    addVertex(Vertex::PC(glm::vec3(-size.x / 2, 0, -size.y / 2), glm::vec4(0.2f, 0.2f, 0.2f, 1)));
    addVertex(Vertex::PC(glm::vec3(size.x / 2, 0, -size.y / 2), glm::vec4(0.2f, 0.2f, 0.2f, 1)));
    addVertex(Vertex::PC(glm::vec3(size.x / 2, 0, size.y / 2), glm::vec4(0.2f, 0.2f, 0.2f, 1)));
    addVertex(Vertex::PC(glm::vec3(-size.x / 2, 0, size.y / 2), glm::vec4(0.2f, 0.2f, 0.2f, 1)));
    end();
}
