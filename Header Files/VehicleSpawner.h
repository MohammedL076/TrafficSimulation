#pragma once

#include <vector>
#include <memory>
#include <random>
#include <glm/glm.hpp>
#include "SceneObject.h"
#include "Entity.h"
#include "ModelLoader.h"

class VehicleSpawner : public SceneObject {
public:
    VehicleSpawner(std::vector<std::shared_ptr<SceneObject>>& sceneObjects,
        const std::vector<std::shared_ptr<Entity>>& stoplights,
        glm::vec3 spawnPosition,
        float direction,
        std::shared_ptr<Model> carModel,
        std::shared_ptr<Model> busModel
    );

    void update(float deltaTime) override;
    void draw() override;

private:
    std::vector<std::shared_ptr<SceneObject>>& sceneObjects;
    std::vector<std::shared_ptr<Entity>> stoplights;
    std::shared_ptr<Model> carModel;
    std::shared_ptr<Model> busModel;

    glm::vec3 spawnPosition; 
    float direction;          

    float spawnInterval;
    float timer;

    std::random_device rd;
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
};
