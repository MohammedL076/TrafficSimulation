#pragma once
#include <memory>
class Entity;

class Component {
public:
	virtual ~Component() = default;


	virtual void update(float deltaTime) {}
	virtual void draw() {}

	void setOwner(Entity* entity) { this->owner = entity; }
	Entity* getOwner() const { return owner; }

protected:
	Entity* owner = nullptr; 

};

