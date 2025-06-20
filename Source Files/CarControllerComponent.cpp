#include "CarControllerComponent.h"
#include "Entity.h"
#include "EntityObject.h"

void CarControllerComponent::update(float deltaTime) {
    if (!transform) return;

    auto nearestStoplight = findNearestStoplight();
    if (!nearestStoplight) {
        transform->position.z += direction * speed * deltaTime;
        return;
    }

    auto stoplight = nearestStoplight->getComponent<StoplightComponent>();
    auto stoplightTransform = nearestStoplight->getComponent<TransformComponent>();
    if (!stoplight || !stoplightTransform) return;

    float stopZ = stoplightTransform->position.z;

    bool approaching = (direction < 0 && transform->position.z > stopZ) ||
        (direction > 0 && transform->position.z < stopZ);

    if (approaching) {
        if (stoplight->getState() == StoplightComponent::State::Red ||
            stoplight->getState() == StoplightComponent::State::Orange ||
            isVehicleAhead(5.0f)) { 
            return; 
        }
    }
    transform->position.z += direction * speed * deltaTime;
}

bool CarControllerComponent::isVehicleAhead(float safeDistance) {
    for (const auto& obj : sceneObjects) {
        auto entityObj = std::dynamic_pointer_cast<EntityObject>(obj);
        if (!entityObj) continue;

        auto other = entityObj->getEntity();
        if (other == selfEntity) continue;

        auto otherTransform = other->getComponent<TransformComponent>();
        if (!otherTransform) continue;

        if (std::abs(otherTransform->position.x - transform->position.x) < 0.1f) {
            float dz = otherTransform->position.z - transform->position.z;

            if ((direction < 0 && dz < 0 && std::abs(dz) < safeDistance) ||
                (direction > 0 && dz > 0 && std::abs(dz) < safeDistance)) {
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<Entity> CarControllerComponent::findNearestStoplight() {
    std::shared_ptr<Entity> closest = nullptr;
    float closestDist = std::numeric_limits<float>::max();

    for (const auto& stoplight : sceneObjects) {
        auto entityObj = std::dynamic_pointer_cast<EntityObject>(stoplight);
        if (!entityObj) continue;

        auto stoplightEntity = entityObj->getEntity();
        if (!stoplightEntity->getComponent<StoplightComponent>()) continue;

        auto stoplightTransform = stoplightEntity->getComponent<TransformComponent>();
        if (!stoplightTransform) continue;

        float dz = stoplightTransform->position.z - transform->position.z;

        if ((direction < 0 && dz < 0) || (direction > 0 && dz > 0)) {
            float dist = std::abs(dz);
            if (dist < closestDist) {
                closestDist = dist;
                closest = stoplightEntity;
            }
        }
    }

    return closest;
}






