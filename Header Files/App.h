#pragma once

#include <memory>
#include <vector>
#include "Renderer.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Streetlight.h"


class App {
public:
    App();
    void init();
    void update(float deltaTime);
    void draw();
    void setAllStoplights(bool green);
    void resetAllStoplights();
    Camera camera;

	float testTimer = 0.0f;
    const float testInterval = 4.0f;

    float fpsTimer = 0.0f;
    int fpsCounter = 0;
    int currentFps = 0;
    std::vector<Streetlight> streetlights;

private:
    std::unique_ptr<Renderer> renderer;
    std::vector<std::shared_ptr<SceneObject>> sceneObjects;
	std::vector<std::shared_ptr<Entity>> stoplightEntities;
	std::shared_ptr<Model> carModel;
	std::shared_ptr<Model> busModel;
};
