#include "EntityObject.h"
#include "StoplightRendererComponent.h"
#include "StreetlampRendererComponent.h" 

void EntityObject::update(float deltaTime) {
    if (entity) {
        entity->update(deltaTime);
    }
}

void EntityObject::draw() {
    if (!entity) return;

    auto meshRenderer = entity->getComponent<MeshRendererComponent>();
    if (meshRenderer)
        meshRenderer->draw();

    auto stoplightRenderer = entity->getComponent<StoplightRendererComponent>();
    if (stoplightRenderer)
        stoplightRenderer->draw();

    auto streetlampRenderer = entity->getComponent<StreetlampRendererComponent>();
    if (streetlampRenderer)
        streetlampRenderer->draw();
}
