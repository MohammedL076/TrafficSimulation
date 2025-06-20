#include "VehicleFactory.h"
#include "TransformComponent.h"
#include "MeshRendererComponent.h"
#include "CarControllerComponent.h"
#include "Entity.h"
#include "RenderComponent.h"

std::shared_ptr<Entity> VehicleFactory::createCarEntity(
    const glm::vec3& position,
    float direction,
    const std::vector<std::shared_ptr<Entity>>& stoplights,
    const std::vector<std::shared_ptr<SceneObject>>& sceneObjects,
    std::shared_ptr<Model> carModel)
{
    auto car = std::make_shared<Entity>();
    auto transform = car->addComponent<TransformComponent>(position);
    auto mesh = car->addComponent<MeshRendererComponent>(transform, carModel);

    auto controller = car->addComponent<CarControllerComponent>(transform,
        getNearestStoplight(position, direction, stoplights),
        sceneObjects,
        car);
    controller->setDirection(direction);
    controller->setSpeed(10.0f);
    return car;
}

std::shared_ptr<Entity> VehicleFactory::createBusEntity(
    const glm::vec3& position,
    float direction,
    const std::vector<std::shared_ptr<Entity>>& stoplights,
    const std::vector<std::shared_ptr<SceneObject>>& sceneObjects)
{
    auto bus = std::make_shared<Entity>();
    auto transform = bus->addComponent<TransformComponent>(position, glm::vec3(0), glm::vec3(1.5f, 1.0f, 2.0f));
    bus->addComponent<RenderComponent>(glm::vec4(1, 1, 0, 1)); 

    auto controller = bus->addComponent<CarControllerComponent>(transform,
        getNearestStoplight(position, direction, stoplights),
        sceneObjects,
        bus);
    controller->setDirection(direction);
    controller->setSpeed(6.0f);
    return bus;
}

std::shared_ptr<Entity> VehicleFactory::getNearestStoplight(
    const glm::vec3& pos, float direction,
    const std::vector<std::shared_ptr<Entity>>& stoplights)
{
    std::shared_ptr<Entity> closest = nullptr;
    float closestDist = std::numeric_limits<float>::max();

    for (const auto& stoplight : stoplights) {
        auto transform = stoplight->getComponent<TransformComponent>();
        if (!transform) continue;

        float dz = transform->position.z - pos.z;

        if ((direction < 0 && dz < 0) || (direction > 0 && dz > 0)) {
            float dist = std::abs(dz);
            if (dist < closestDist) {
                closestDist = dist;
                closest = stoplight;
            }
        }
    }

    return closest;
}





