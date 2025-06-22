#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Entity.h"
#include "Constants.h"
#include "tigl.h"
#include <glm/glm.hpp>
#include <cmath>

class StreetlampRendererComponent : public RenderComponent {
public:
    void draw() override {
        using namespace tigl;

        auto transform = getOwner()->getComponent<TransformComponent>();
        if (!transform) return;

        shader->enableColor(true);
        shader->setModelMatrix(transform->getTransformMatrix());

        // paal
        glm::vec4 poleColor = glm::vec4(0.95f, 0.95f, 0.95f, 1.0f);  
        float poleHeight = STREETLAMP_HEIGHT;   
        float poleWidth = STREETLAMP_WIDTH;   

        for (int i = 0; i < 2; ++i) {
            float angle = glm::radians(90.0f * i);
            glm::vec3 offset = glm::vec3(cos(angle), 0, sin(angle)) * poleWidth;

            tigl::begin(GL_QUADS);
            tigl::addVertex(Vertex::PC(offset + glm::vec3(0, 0.0f, 0), poleColor));
            tigl::addVertex(Vertex::PC(-offset + glm::vec3(0, 0.0f, 0), poleColor));
            tigl::addVertex(Vertex::PC(-offset + glm::vec3(0, poleHeight, 0), poleColor));
            tigl::addVertex(Vertex::PC(offset + glm::vec3(0, poleHeight, 0), poleColor));
            tigl::end();
        }

        // Gouden bol bovenop
        tigl::begin(GL_TRIANGLE_FAN);
        glm::vec4 lightColor = glm::vec4(1.0f, 0.85f, 0.3f, 1.0f); 
        glm::vec3 topCenter(0.0f, poleHeight + 0.35f, 0.0f);
        tigl::addVertex(Vertex::PC(topCenter, lightColor));

        int segments = CIRCLE_SEGMENTS;
        float radius = LAMP_RADIUS;
        for (int i = 0; i <= segments; ++i) {
            float angle = i * 2.0f * 3.1415926f / segments;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            tigl::addVertex(Vertex::PC(glm::vec3(x, topCenter.y + y, 0.0f), lightColor));
        }
        tigl::end();
    }
    StreetlampRendererComponent(const glm::vec4& color)
        : RenderComponent(color) {
    }

};
