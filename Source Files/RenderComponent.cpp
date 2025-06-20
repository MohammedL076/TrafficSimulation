#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace tigl;

RenderComponent::RenderComponent(const glm::vec4& color) : color(color) {}

void RenderComponent::draw() {
	auto transform = owner->getComponent<TransformComponent>();
	if (!transform) return;

	glm::mat4 model = glm::translate(glm::mat4(1.0f), transform->position);
	shader->setModelMatrix(model);

	begin(GL_QUADS);
	addVertex(Vertex::PC(glm::vec3(-1, 0, -1), color));
	addVertex(Vertex::PC(glm::vec3(-1, 0, 1), color));
	addVertex(Vertex::PC(glm::vec3(1, 0, 1), color));
	addVertex(Vertex::PC(glm::vec3(1, 0, -1), color));
	end();
}