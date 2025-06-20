#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"

class TransformComponent : public Component {
public:
    glm::vec3 position = { 0, 0, 0 };
    glm::vec3 rotation = { 0, 0, 0 };
    glm::vec3 scale = { 1, 1, 1 };

    TransformComponent(
        const glm::vec3& pos = { 0, 0, 0 },
        const glm::vec3& rot = { 0, 0, 0 },
        const glm::vec3& scl = { 1, 1, 1 }
    );

    glm::mat4 getTransformMatrix() const;
};
