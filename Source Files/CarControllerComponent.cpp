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
    float carLength = 4.0f;
    float carFront = transform->position.z + (direction * carLength * 0.5f);

    bool approaching = (direction < 0 && carFront > stopZ) ||
        (direction > 0 && carFront < stopZ);

    if (approaching) {
        if (stoplight->getState() == StoplightComponent::State::Red ||
            stoplight->getState() == StoplightComponent::State::Orange ||
            isVehicleAhead(2.5f)) { 
            return;
        }
    }
    transform->position.z += direction * speed * deltaTime;
}

bool CarControllerComponent::isVehicleAhead(float safeDistance) {
    float carLength = 4.0f;
    float myFront = transform->position.z + (direction * carLength * 0.5f);

    for (const auto& obj : sceneObjects) {
        auto entityObj = std::dynamic_pointer_cast<EntityObject>(obj);
        if (!entityObj) continue;

        auto other = entityObj->getEntity();
        if (other == selfEntity) continue;

        auto otherTransform = other->getComponent<TransformComponent>();
        if (!otherTransform) continue;

        float otherLength = 4.0f;
        float otherBack = otherTransform->position.z - (direction * otherLength * 0.5f);

        if (std::abs(otherTransform->position.x - transform->position.x) < 0.1f) {
            float dz = otherBack - myFront;
            auto otherController = other->getComponent<CarControllerComponent>();
            bool otherStopped = otherController && otherController->speed < 0.1f;
            if (((direction < 0 && dz < 0 && std::abs(dz) < safeDistance) ||
                (direction > 0 && dz > 0 && std::abs(dz) < safeDistance))
                && otherStopped) {
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






