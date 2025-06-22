// CarControllerComponent.cpp
#include "CarControllerComponent.h"
#include "Entity.h"
#include "EntityObject.h"
#include "Constants.h"

void CarControllerComponent::update(float deltaTime) {
    if (!transform) return;

    bool shouldStop = false;

    auto nearestStoplight = findNearestStoplight();
    if (nearestStoplight) {
        auto stoplight = nearestStoplight->getComponent<StoplightComponent>();
        auto stoplightTransform = nearestStoplight->getComponent<TransformComponent>();

        if (stoplight && stoplightTransform) {
            float stopZ = stoplightTransform->position.z;
            float carFront = transform->position.z + (direction * vehicleLength * 0.5f);
            float buffer = (vehicleLength > 4.0f) ? 1.0f : 0.5f;

            bool atStopline = (direction < 0 && carFront <= stopZ + buffer) ||
                (direction > 0 && carFront >= stopZ - buffer);

            if (stoplight->getState() == StoplightComponent::State::Red && atStopline) {
                shouldStop = true;
            }
            else if (stoplight->getState() == StoplightComponent::State::Orange && atStopline) {
                if (std::abs(carFront - stopZ) < ORANGE_STOP_DISTANCE) {
                    shouldStop = true;
                }
            }
        }
    }
    if (isVehicleAhead(SAFE_DISTANCE)) {
        shouldStop = true;
    }

    if (!shouldStop) {
        transform->position.z += direction * speed * deltaTime;
    }
}

bool CarControllerComponent::isVehicleAhead(float safeDistance) {
    float myFront = transform->position.z + (direction * vehicleLength * 0.5f);

    for (const auto& obj : sceneObjects) {
        auto entityObj = std::dynamic_pointer_cast<EntityObject>(obj);
        if (!entityObj) continue;

        auto other = entityObj->getEntity();
        if (other == selfEntity) continue;

        auto otherTransform = other->getComponent<TransformComponent>();
        auto otherController = other->getComponent<CarControllerComponent>();
        if (!otherTransform || !otherController) continue;

        if (std::abs(otherTransform->position.x - transform->position.x) > 0.1f)
            continue;

        float otherLength = otherController->vehicleLength; 
        float otherBack = otherTransform->position.z - (direction * otherLength * 0.5f);

        float distance = (direction > 0)
            ? otherBack - myFront
            : myFront - otherBack;

        if (distance > 0 && distance < safeDistance)
            return true;
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
