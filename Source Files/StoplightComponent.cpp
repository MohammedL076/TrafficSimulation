#include "StoplightComponent.h"
#include <random>
#include "Constants.h"

StoplightComponent::StoplightComponent() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 5.0f);
    offset = dist(rng);
}

void StoplightComponent::update(float deltaTime) {
    timer += deltaTime;

    if (manualOverride) {
        state = overrideState;
        return;
    }

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

void StoplightComponent::setGreen(bool green) {
    manualOverride = true;
    overrideState = green ? State::Green : State::Red;
}

void StoplightComponent::clearManualOverride() {
    manualOverride = false;
}

