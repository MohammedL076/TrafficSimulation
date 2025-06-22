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
#include "Constants.h"
#include "ModelLoader.h"
#include "UnitTest.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <StreetlampRendererComponent.h>
#include "tigl.h"
using namespace tigl;

App::App() {
    renderer = std::make_unique<Renderer>();
}

void App::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init("#version 130"); 

    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(glfwGetCurrentContext(), [](GLFWwindow* window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
            return;
        }
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (app) {
            app->camera.processKeyboard(key, action);

            if (action == GLFW_PRESS) {
                if (key == GLFW_KEY_G) {
                    app->setAllStoplights(true);
                } else if (key == GLFW_KEY_R) {
                    app->setAllStoplights(false);
                } else if (key == GLFW_KEY_T) {
                    app->resetAllStoplights();
                    std::cout << "Handmatige override uitgeschakeld – terug naar automatische stoplichten\n";
                }
            }
        }
        });
    renderer->init();

    for (float z = -STOPLIGHT_INTERVAL; z <= STOPLIGHT_INTERVAL; z += STOPLIGHT_INTERVAL)
    {
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
    try {
        busModel = std::make_shared<Model>();
        if (!ModelLoader::load("Resource Files/Vehicles/low-poly/Bus-Model/bus.obj", *busModel)) {
            std::cerr << "Kon het bus-model niet laden!" << std::endl;
        }
        carModel = std::make_shared<Model>();
        if (!ModelLoader::load("Resource Files/Vehicles/low-poly/Car-Model/Car.obj", *carModel)) {
            std::cerr << "Kon het auto-model niet laden!" << std::endl;
        }
    }
	catch (const std::exception& e) {
		std::cerr << "Fout bij het laden van modellen: " << e.what() << std::endl;
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
		return;
	}

    auto rightSpawner = std::make_shared<VehicleSpawner>(
        sceneObjects, stoplightEntities, glm::vec3(3, 0.1f, 270), -1.0f, carModel, busModel);
    auto leftSpawner = std::make_shared<VehicleSpawner>(
        sceneObjects, stoplightEntities, glm::vec3(-3, 0.1f, -270), 1.0f, carModel, busModel);
    sceneObjects.push_back(rightSpawner);
    sceneObjects.push_back(leftSpawner);

    sceneObjects.push_back(std::make_shared<Road>(glm::vec3(0, 0, 0), glm::vec2(10, 750)));

    for (float z = -300.0f; z <= 300.0f; z += STREETLAMP_INTERVAL) {
        auto lamp = std::make_shared<Entity>();
        lamp->addComponent<TransformComponent>(glm::vec3(10.0f, 0.0f, z)); 
        lamp->addComponent<StreetlampRendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        sceneObjects.push_back(std::make_shared<EntityObject>(lamp));

        streetlights.push_back({ glm::vec3(10.0f, 5.3f, z), glm::vec3(0.8f, 0.8f, 0.6f) });
    }
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

	fpsTimer += deltaTime;
	fpsCounter++;

	if (fpsTimer >= 1.0f) {
		currentFps = fpsCounter;
		fpsCounter = 0;
		fpsTimer = 0.0f;

		std::cout << "FPS: " << currentFps << std::endl;
	}
    testTimer += deltaTime;
    if (testTimer >= testInterval) {
        try {
            testAantalVoertuigen(sceneObjects);
        }
        catch (const std::exception& e) {
            std::cerr << "Fout bij unit-test: " << e.what() << std::endl;
        }
        testTimer = 0.0f;
    }


}


void App::draw() {
    renderer->beginDraw(streetlights);

    for (const auto& obj : sceneObjects) {
        if (obj)
            obj->draw();
    }

    renderer->endDraw();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 60), ImGuiCond_Always);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs;

    ImGui::Begin("Performance", nullptr, window_flags);
    ImGui::Text("FPS: %d", currentFps);
    ImGui::Text("Voertuigen: %d", laatsteVoertuigCount);  
    ImGui::End();  

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void App::setAllStoplights(bool green) {
    std::cout << "Toets ingedrukt! Alles op " << (green ? "groen" : "rood") << std::endl;

    for (const auto& ent : stoplightEntities) {
        auto stoplight = ent->getComponent<StoplightComponent>();
        if (stoplight) {
            stoplight->setGreen(green);
        }
    }
}

void App::resetAllStoplights() {
    for (const auto& ent : stoplightEntities) {
        auto stoplight = ent->getComponent<StoplightComponent>();
        if (stoplight) {
            stoplight->clearManualOverride();
        }
    }
}


