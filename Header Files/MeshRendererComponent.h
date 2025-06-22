#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "ModelLoader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "tigl.h"

class MeshRendererComponent : public RenderComponent {
public:
    MeshRendererComponent(std::shared_ptr<TransformComponent> transform, std::shared_ptr<Model> model)
        : RenderComponent(glm::vec4(1.0f, 0.9f, 0.0f, 1.0f)), transform(transform), model(model) {
    }

    void draw() override {
        if (!transform || !model) return;

        using namespace tigl;
        shader->setModelMatrix(transform->getTransformMatrix());

        for (size_t i = 0; i < model->faces.size(); ++i) {
            int matIndex = (i < model->faceMaterialIndices.size()) ? model->faceMaterialIndices[i] : -1;
            const Material* mat = (matIndex >= 0 && matIndex < (int)model->materials.size()) ? &model->materials[matIndex] : nullptr;

            bool hasTexture = mat && mat->textureID;
            if (hasTexture) {
                shader->enableTexture(true);
                glBindTexture(GL_TEXTURE_2D, mat->textureID);
            }
            else {
                shader->enableTexture(false);
                shader->enableColor(true);
            }

            tigl::begin(GL_POLYGON);
            for (const auto& fv : model->faces[i].vertices) {
                glm::vec3 pos = (fv.vertexIndex >= 0 && fv.vertexIndex < (int)model->vertices.size())
                    ? model->vertices[fv.vertexIndex]
                    : glm::vec3(0, 0, 0);

                glm::vec3 normal = glm::vec3(0, 1, 0); 
                if (fv.normalIndex >= 0 && fv.normalIndex < (int)model->normals.size()) {
                    normal = model->normals[fv.normalIndex];
                }

                if (hasTexture) {
                    glm::vec2 uv = (fv.texcoordIndex >= 0 && fv.texcoordIndex < (int)model->texcoords.size())
                        ? model->texcoords[fv.texcoordIndex]
                        : glm::vec2(0, 0);
                    tigl::addVertex(Vertex::PTN(pos, uv, normal));
                }
                else {
                    glm::vec4 color = mat ? glm::vec4(mat->diffuse, 1.0f) : glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
                    tigl::addVertex(Vertex::PCN(pos, color, normal));
                }
            }
            tigl::end();
        }

        shader->enableTexture(false);
        shader->enableColor(false);
    }

private:
    std::shared_ptr<TransformComponent> transform;
    std::shared_ptr<Model> model;
};
