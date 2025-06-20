#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Entity.h"
#include "SceneObject.h"

class SceneObject;
struct Model;

class VehicleFactory {
public:
    static std::shared_ptr<Entity> createCarEntity(
        const glm::vec3& position,
        float direction,
        const std::vector<std::shared_ptr<Entity>>& stoplights,
        const std::vector<std::shared_ptr<SceneObject>>& sceneObjects,
        std::shared_ptr<Model> carModel);

    static std::shared_ptr<Entity> createBusEntity(
        const glm::vec3& position,
        float direction,
        const std::vector<std::shared_ptr<Entity>>& stoplights,
        const std::vector<std::shared_ptr<SceneObject>>& sceneObjects);

    static std::shared_ptr<Entity> getNearestStoplight(
        const glm::vec3& pos,
        float direction,
        const std::vector<std::shared_ptr<Entity>>& stoplights);
};
