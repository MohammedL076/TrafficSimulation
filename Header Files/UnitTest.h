#pragma once
#include <vector>
#include <memory>

class SceneObject;

extern int laatsteVoertuigCount;
void testAantalVoertuigen(const std::vector<std::shared_ptr<SceneObject>>& sceneObjects);
