#pragma once

#include "Component.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class RenderComponent : public Component {
public:
	RenderComponent(const glm::vec4& color);

	void draw() override;

private:
	glm::vec4 color;
};
