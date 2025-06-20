#include "EntityObject.h"
#include "StoplightRendererComponent.h"

void EntityObject::update(float deltaTime) {
	if (entity) {
		entity->update(deltaTime);
	}
}

void EntityObject::draw() {
	if (!entity) return;
		auto Meshrenderer = entity->getComponent<MeshRendererComponent>();
		if (Meshrenderer)
			Meshrenderer->draw();

		auto stoplightRenderer = entity->getComponent<StoplightRendererComponent>();
		if (stoplightRenderer)
			stoplightRenderer->draw();
}