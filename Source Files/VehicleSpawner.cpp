// VehicleSpawner.cpp
#include "VehicleSpawner.h"
#include "VehicleFactory.h"
#include "SceneObject.h"
#include "EntityObject.h"
#include "TransformComponent.h"
#include "Constants.h"
#include <random>

VehicleSpawner::VehicleSpawner(
    std::vector<std::shared_ptr<SceneObject>>& sceneObjects,
    const std::vector<std::shared_ptr<Entity>>& stoplights,
    glm::vec3 spawnPosition,
    float direction,
    std::shared_ptr<Model> carModel,
    std::shared_ptr<Model> busModel
) : sceneObjects(sceneObjects), stoplights(stoplights),
spawnPosition(spawnPosition), direction(direction),
spawnInterval(VEHICLE_SPAWN_INTERVAL), timer(0.0f),
carModel(carModel), busModel(busModel),
rng(std::random_device{}()), dist(0.0f, 1.0f) {
}

void VehicleSpawner::update(float deltaTime) {
    timer += deltaTime;

    bool canSpawn = true;
    float safeZone = VEHICLE_SAFE_ZONE; 
    for (auto& obj : sceneObjects) {
        auto entityObj = std::dynamic_pointer_cast<EntityObject>(obj);
        if (!entityObj) continue;
        auto entity = entityObj->getEntity();
        auto t = entity->getComponent<TransformComponent>();
        if (!t) continue;

        bool sameLane = std::abs(t->position.x - spawnPosition.x) < VEHICLE_LANE_WIDTH;
        bool tooClose = std::abs(t->position.z - spawnPosition.z) < safeZone;

        if (sameLane && tooClose) {
            canSpawn = false;
            break;
        }
    }

    if (timer >= spawnInterval && canSpawn) {
        timer = 0.0f;

        bool spawnBus = dist(rng) > 0.7f;
        glm::vec3 pos = spawnPosition;

        auto vehicle = spawnBus ?
            VehicleFactory::createBusEntity(pos, direction, stoplights, sceneObjects, busModel) :
            VehicleFactory::createCarEntity(pos, direction, stoplights, sceneObjects, carModel);

        sceneObjects.push_back(std::make_shared<EntityObject>(vehicle));
    }
}

void VehicleSpawner::draw() {}