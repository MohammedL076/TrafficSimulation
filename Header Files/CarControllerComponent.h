#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "StoplightComponent.h"
#include "SceneObject.h"
#include "Entity.h"
#include <memory>
#include <vector>

class CarControllerComponent : public Component {
public:
    CarControllerComponent(std::shared_ptr<TransformComponent> transform,
        std::shared_ptr<Entity> stoplightEntity,
        const std::vector<std::shared_ptr<SceneObject>>& sceneObjects,
        std::shared_ptr<Entity> selfEntity)
        : transform(transform),
        stoplightEntity(stoplightEntity),
        sceneObjects(sceneObjects),
        selfEntity(selfEntity) {
    }

    void update(float deltaTime) override;
    void setSpeed(float s) { speed = s; }
    void setDirection(float dir) { direction = dir; }
    bool isVehicleAhead(float safeDistance);
    std::shared_ptr<Entity> findNearestStoplight(); 


    float vehicleLength = 4.0f;

private:
    std::shared_ptr<TransformComponent> transform;
    std::shared_ptr<Entity> stoplightEntity;
    std::shared_ptr<Entity> selfEntity;
    const std::vector<std::shared_ptr<SceneObject>>& sceneObjects;
    float speed = 5.0f;
    float direction = -1.0f;
};
