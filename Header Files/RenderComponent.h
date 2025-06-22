#pragma once

#include "Component.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class RenderComponent : public Component {
public:
	RenderComponent(const glm::vec4& color);

	virtual void draw() = 0;
	virtual ~RenderComponent() = default;

protected:
	glm::vec4 color;
};
