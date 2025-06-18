// App.cpp
#include "App.h"
#include "Road.h"
#include "Car.h"
#include <GLFW/glfw3.h>


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

    renderer->init();

	auto road = std::make_shared<Road>(glm::vec3(0, 0, 0), glm::vec2(10, 100));
	sceneObjects.push_back(road);
    auto car = std::make_shared<Car>(glm::vec3(0, 0.05f, 10));
    sceneObjects.push_back(car);

}

void App::update(float deltaTime) {
	for (auto& obj : sceneObjects)
		obj->update(deltaTime);
	camera.update(deltaTime);
	renderer->setViewMatrix(camera.getViewMatrix());
}

void App::draw() {
    renderer->beginDraw();

    for (auto& obj : sceneObjects)
        obj->draw();

    renderer->endDraw();
}
