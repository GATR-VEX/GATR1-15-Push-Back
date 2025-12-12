#pragma once

#include <cstdint>

namespace robot {
namespace ports {
// Drive motors (8 total)
inline constexpr std::int8_t DRIVE_RIGHT_FRONT = 17;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE = 19;
inline constexpr std::int8_t DRIVE_RIGHT_REAR = 20;
inline constexpr std::int8_t DRIVE_RIGHT_AUX = -18;

inline constexpr std::int8_t DRIVE_LEFT_FRONT = -14;
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE = 12;
inline constexpr std::int8_t DRIVE_LEFT_REAR = -11;
inline constexpr std::int8_t DRIVE_LEFT_AUX = -13;

// Intake motors (3 total)
inline constexpr std::int8_t INTAKE_STAGE_1 = 2;  // TODO: Set port for first stage intake motor
inline constexpr std::int8_t INTAKE_STAGE_2 = -10;  // TODO: Set port for second stage intake motor
inline constexpr std::int8_t INTAKE_INDEXER = -21;  // TODO: Set port for indexer motor

// Pneumatics
inline constexpr std::int8_t PISTON_MATCHLOADER = 7;  // TODO: Set ADI port for matchloader piston
inline constexpr std::int8_t PISTON_INDEXER = 8;      // TODO: Set ADI port for indexer piston
inline constexpr std::int8_t PISTON_WINGS = 0;        // TODO: Set ADI port for wings piston

// Sensors
inline constexpr std::int8_t IMU = 1;
inline constexpr std::int8_t VERTICAL_ROTATION = 15;
inline constexpr std::int8_t HORIZONTAL_ROTATION = 16;
inline constexpr std::int8_t OPTICAL_COLOR_SORT = 0;  // TODO: Set port for color sort optical sensor
}  // namespace ports
}  // namespace robot

