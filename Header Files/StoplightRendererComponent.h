#pragma once
#include "Component.h"
#include "StoplightComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
using namespace tigl;

class StoplightRendererComponent : public Component {
public:
    void drawCircle(const glm::vec3& center, float radius, const glm::vec4& color) {
        const int segments = 32;
        tigl::begin(GL_TRIANGLE_FAN);
        tigl::addVertex(Vertex::PC(center, color));
        for (int i = 0; i <= segments; ++i) {
            float angle = i * 2.0f * 3.1415926f / segments;
            float x = center.x + cos(angle) * radius;
            float y = center.y + sin(angle) * radius;
            tigl::addVertex(Vertex::PC(glm::vec3(x, y, center.z), color));
        }
        tigl::end();
    }

    void draw() override {
        auto stoplight = getOwner()->getComponent<StoplightComponent>();
        if (!stoplight) return;

        auto transform = getOwner()->getComponent<TransformComponent>();
        tigl::shader->enableColor(true);
        tigl::shader->setModelMatrix(transform->getTransformMatrix());

        // Paal (groter)
        tigl::begin(GL_QUADS);
        tigl::addVertex(Vertex::PC(glm::vec3(-0.10f, 0.0f, 0.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1)));
        tigl::addVertex(Vertex::PC(glm::vec3(0.10f, 0.0f, 0.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1)));
        tigl::addVertex(Vertex::PC(glm::vec3(0.10f, 2.0f, 0.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1)));
        tigl::addVertex(Vertex::PC(glm::vec3(-0.10f, 2.0f, 0.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1)));
        tigl::end();

        // Kast (groter)
        tigl::begin(GL_QUADS);
        tigl::addVertex(Vertex::PC(glm::vec3(-0.30f, 2.0f, 0.10f), glm::vec4(0, 0, 0, 1)));
        tigl::addVertex(Vertex::PC(glm::vec3(0.30f, 2.0f, 0.10f), glm::vec4(0, 0, 0, 1)));
        tigl::addVertex(Vertex::PC(glm::vec3(0.30f, 2.8f, 0.10f), glm::vec4(0, 0, 0, 1)));
        tigl::addVertex(Vertex::PC(glm::vec3(-0.30f, 2.8f, 0.10f), glm::vec4(0, 0, 0, 1)));
        tigl::end();

        // Lampen (groter en verder uit elkaar)
        glm::vec4 red = stoplight->getState() == StoplightComponent::State::Red ? glm::vec4(1, 0, 0, 1) : glm::vec4(0.2f, 0, 0, 1);
        glm::vec4 orange = stoplight->getState() == StoplightComponent::State::Orange ? glm::vec4(1, 0.5f, 0, 1) : glm::vec4(0.2f, 0.1f, 0, 1);
        glm::vec4 green = stoplight->getState() == StoplightComponent::State::Green ? glm::vec4(0, 1, 0, 1) : glm::vec4(0, 0.2f, 0, 1);

        drawCircle(glm::vec3(0, 2.65f, 0.12f), 0.14f, red);
        drawCircle(glm::vec3(0, 2.40f, 0.12f), 0.14f, orange);
        drawCircle(glm::vec3(0, 2.15f, 0.12f), 0.14f, green);
    }
};
