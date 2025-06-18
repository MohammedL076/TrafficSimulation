#pragma once
#include "SceneObject.h"
#include <glm/glm.hpp>

class Car : public SceneObject {
public:
    Car(const glm::vec3& position);
    void update(float deltaTime) override;
    void draw() override;

private:
    glm::vec3 position;
    float speed = 5.0f; 
};
