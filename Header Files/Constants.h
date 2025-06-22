#pragma once
#pragma once

// Stoplicht timing
constexpr float GREEN_DURATION = 25.0f;
constexpr float RED_DURATION = 20.0f;
constexpr float ORANGE_DURATION = 10.0f;

// Posities en afstanden
constexpr float LANE_X = 3.0f;
constexpr float CAR_START_Z = 10.0f;
constexpr float STOPLIGHT_Z = 2.0f;
constexpr float STOPLIGHT_INTERVAL = 100.0f;
constexpr float STREETLAMP_INTERVAL = 200.0f;

// Straatlantaarn
constexpr float STREETLAMP_HEIGHT = 5.0f;
constexpr float STREETLAMP_WIDTH = 0.12f;
constexpr float LAMP_RADIUS = 0.25f;
constexpr int CIRCLE_SEGMENTS = 32;

// Spawnlogica
constexpr float VEHICLE_SPAWN_INTERVAL = 12.0f;
constexpr float VEHICLE_SAFE_ZONE = 10.0f;
constexpr float VEHICLE_LANE_WIDTH = 1.0f;

// Verkeersveiligheid
constexpr float SAFE_DISTANCE = 5.5f;
constexpr float ORANGE_STOP_DISTANCE = 6.0f;
