#pragma once

#include "SceneObject.h"
#include <glm/glm.hpp>

class Road : public SceneObject {
public:
    Road(const glm::vec3& position, const glm::vec2& size);
    void update(float deltaTime) override;
    void draw() override;

private:
    glm::vec3 position;
    glm::vec2 size;
};
