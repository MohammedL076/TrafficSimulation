#include "StoplightComponent.h"
#include <random>

const float GREEN_DURATION = 25.0f;
const float RED_DURATION = 20.0f;
const float ORANGE_DURATION = 10.0f;

StoplightComponent::StoplightComponent() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 5.0f);
    offset = dist(rng);
}

void StoplightComponent::update(float deltaTime) {
    timer += deltaTime;

    const float totalCycleDuration = GREEN_DURATION + ORANGE_DURATION + RED_DURATION;

    float adjustedTime = fmod(timer + offset, totalCycleDuration);

    if (adjustedTime < GREEN_DURATION) {
        state = State::Green;
    }
    else if (adjustedTime < GREEN_DURATION + ORANGE_DURATION) {
        state = State::Orange;
    }
    else {
        state = State::Red;
    }
}


StoplightComponent::State StoplightComponent::getState() const {
    return state;
}
