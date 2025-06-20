#pragma once

#include <memory>
#include <vector>
#include "Renderer.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Entity.h"
#include "TransformComponent.h"


class App {
public:
    App();
    void init();
    void update(float deltaTime);
    void draw();

    Camera camera;

private:
    std::unique_ptr<Renderer> renderer;
    std::vector<std::shared_ptr<SceneObject>> sceneObjects;
	std::vector<std::shared_ptr<Entity>> stoplightEntities;
};
