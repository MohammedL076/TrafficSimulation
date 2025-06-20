#pragma once
#include <vector>
#include <memory>
#include "Component.h"

class Entity {
public:
	template<typename T, typename... Args>
	std::shared_ptr<T> addComponent(Args&&... args) {
		auto component = std::make_shared<T>(std::forward<Args>(args)...);
		component->setOwner(this);
		components.push_back(component);
		return component;
	}

	template<typename T>
	std::shared_ptr<T> getComponent() {
		for (auto& comp : components) {
			if (auto casted = std::dynamic_pointer_cast<T>(comp)) {
				return casted;
			}
		}
		return nullptr;
	}

	void update(float deltaTime) {
		for (auto& comp : components)
			comp->update(deltaTime);
	}

	void draw() {
		for (auto& comp : components) {
			comp->draw();
		}
	}

private:
	std::vector<std::shared_ptr<Component>> components;
};
