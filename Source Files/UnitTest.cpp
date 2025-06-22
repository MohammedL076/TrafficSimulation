#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include "EntityObject.h"
#include "CarControllerComponent.h"
#include <ctime>  

int laatsteVoertuigCount = 0;

void testAantalVoertuigen(const std::vector<std::shared_ptr<SceneObject>>& sceneObjects) {
    int voertuigCount = 0;

    for (const auto& obj : sceneObjects) {
        if (!obj) continue;
        auto entityObj = std::dynamic_pointer_cast<EntityObject>(obj);
        if (!entityObj) continue;

        auto entity = entityObj->getEntity();
        if (!entity) continue;

        if (entity->getComponent<CarControllerComponent>())
            voertuigCount++;
    }

    laatsteVoertuigCount = voertuigCount;

    auto now = std::chrono::system_clock::now();
    std::time_t tijd = std::chrono::system_clock::to_time_t(now);
    std::tm tijdStruct;
    localtime_s(&tijdStruct, &tijd);

    char tijdBuffer[10];
    strftime(tijdBuffer, sizeof(tijdBuffer), "%H:%M:%S", &tijdStruct);

    std::ofstream out("unit_test_output.txt", std::ios::app);
    if (!out.is_open()) {
        throw std::runtime_error("Kon het testbestand niet openen!");
    }


    out << "[" << tijdBuffer << "] Aantal voertuigen met CarControllerComponent: "
        << voertuigCount << std::endl;

    out.close();
    std::cout << "Voertuigentest uitgevoerd: " << voertuigCount << " voertuigen gevonden.\n";
}


