// App.cpp
#include "App.h"
#include "Road.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "MeshRendererComponent.h"
#include "EntityObject.h"
#include "Camera.h"
#include "Renderer.h"
#include "StoplightComponent.h"
#include "StoplightRendererComponent.h"
#include "CarControllerComponent.h"
#include "VehicleSpawner.h"
#include "VehicleFactory.h"
#include "ModelLoader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


App::App() {
    renderer = std::make_unique<Renderer>();
}

void App::init() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(glfwGetCurrentContext(), [](GLFWwindow* window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
            return;
        }
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (app) app->camera.processKeyboard(key, action);
        });

    float laneX = 3.0f;
    float carStartZ = 10.0f;
    float stoplightZ = 2.0f;

    renderer->init();

    for (float z = -100.0f; z <= 100.0f; z += 100.0f) {
        auto right = std::make_shared<Entity>();
        right->addComponent<TransformComponent>(glm::vec3(4.5f, 0.05f, z));
        right->addComponent<StoplightComponent>();
        right->addComponent<StoplightRendererComponent>();
        stoplightEntities.push_back(right);
        sceneObjects.push_back(std::make_shared<EntityObject>(right));

        auto left = std::make_shared<Entity>();
        left->addComponent<TransformComponent>(
            glm::vec3(-4.5f, 0.05f, z),
            glm::vec3(0, glm::radians(180.0f), 0),
            glm::vec3(1, 1, 1)
        );
        left->addComponent<StoplightComponent>();
        left->addComponent<StoplightRendererComponent>();
        stoplightEntities.push_back(left);
        sceneObjects.push_back(std::make_shared<EntityObject>(left));
    }

    auto busModel = std::make_shared<Model>();
    if (!ModelLoader::load("Resource Files/Vehicles/low-poly/Bus-Model/bus.obj", *busModel)) {
        std::cerr << "Kon het bus-model niet laden!" << std::endl;
    }
    auto carModel = std::make_shared<Model>();
    if (!ModelLoader::load("Resource Files/Vehicles/low-poly/Car-Model/Car.obj", *carModel)) {
        std::cerr << "Kon het auto-model niet laden!" << std::endl;
    }

    auto rightSpawner = std::make_shared<VehicleSpawner>(
        sceneObjects, stoplightEntities, glm::vec3(3, 0.1f, 270), -1.0f, carModel, busModel);
    auto leftSpawner = std::make_shared<VehicleSpawner>(
        sceneObjects, stoplightEntities, glm::vec3(-3, 0.1f, -270), 1.0f, carModel, busModel);
    sceneObjects.push_back(rightSpawner);
    sceneObjects.push_back(leftSpawner);

    sceneObjects.push_back(std::make_shared<Road>(glm::vec3(0, 0, 0), glm::vec2(10, 750)));

}


void App::update(float deltaTime) {

    for (size_t i = 0; i < sceneObjects.size(); ++i) {
        if (sceneObjects[i]) {
            sceneObjects[i]->update(deltaTime);
        }
        else {
            std::cout << "Null sceneObject at index: " << i << std::endl;
        }
    }
    camera.update(deltaTime);
    renderer->setViewMatrix(camera.getViewMatrix());
}


void App::draw() {
    renderer->beginDraw();

    for (const auto& obj : sceneObjects) {
        if (obj)
            obj->draw();
    }

    renderer->endDraw();
}

