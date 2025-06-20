#pragma once
#include "Component.h"
#include <chrono>

class StoplightComponent : public Component {
public:
	enum class State {Red, Green, Orange};
	StoplightComponent();

	void update(float deltaTime) override;
	State getState() const;

private:
	State state = State::Green;
	float timer = 0.0f;
	float switchInterval = 6.0f;
	float offset = 0.0f;
};
