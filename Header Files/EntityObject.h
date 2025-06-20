#pragma once
#include "SceneObject.h"
#include "Entity.h"
#include "MeshRendererComponent.h"
#include "Component.h"

class EntityObject : public SceneObject {
public:
	std::shared_ptr<Entity> getEntity() const { return entity; }
	EntityObject(std::shared_ptr<Entity> e ) : entity(e) {}
	void update(float deltaTime) override;
	void draw() override;
private:
	std::shared_ptr<Entity> entity;

};
