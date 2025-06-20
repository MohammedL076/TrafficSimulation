#include "VehicleSpawner.h"
#include "VehicleFactory.h"
#include "SceneObject.h"
#include "EntityObject.h"
#include "StoplightComponent.h"
#include "ModelLoader.h"
#include "CarControllerComponent.h"

#include <random>

VehicleSpawner::VehicleSpawner(
    std::vector<std::shared_ptr<SceneObject>>& sceneObjects,
    const std::vector<std::shared_ptr<Entity>>& stoplights,
    glm::vec3 spawnPosition,
    float direction,
    std::shared_ptr<Model> carModel 
)
    : sceneObjects(sceneObjects),
    stoplights(stoplights),
    spawnPosition(spawnPosition),
    direction(direction),
    spawnInterval(15.0f),
    timer(0.0f),
    carModel(carModel), 
    rng(std::random_device{}()),
    dist(0.0f, 1.0f)
{
}



void VehicleSpawner::update(float deltaTime) {
    timer += deltaTime;

    if (timer >= spawnInterval) {
        timer = 0.0f;

        bool fromTop = dist(rng) > 0.5f;
        bool spawnBus = dist(rng) > 0.7f; 
        float direction = fromTop ? -1.0f : 1.0f;


        glm::vec3 spawnPos;
        std::shared_ptr<Entity> relevantStoplight;

        if (fromTop) {
            spawnPos = glm::vec3(3, 0.1f, 270); 
        }
        else {
            spawnPos = glm::vec3(-3, 0.1f, -270); 
        }

        std::shared_ptr<Entity> vehicle;
        if (spawnBus) {
            vehicle = VehicleFactory::createBusEntity(spawnPos, direction, stoplights, sceneObjects);
        }
        else {
            vehicle = VehicleFactory::createCarEntity(spawnPos, direction, stoplights, sceneObjects, carModel);

        }
        sceneObjects.push_back(std::make_shared<EntityObject>(vehicle));
    }
}

void VehicleSpawner::draw() {
	// Spawner doesn't need to draw anything
}
