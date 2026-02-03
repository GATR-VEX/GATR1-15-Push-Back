#pragma once

#include <cstdint>

namespace robot {
namespace ports {
// Drive motors (8 total)
inline constexpr std::int8_t DRIVE_RIGHT_FRONT      = 17;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE     = -18;
inline constexpr std::int8_t DRIVE_RIGHT_REAR       = 19;
inline constexpr std::int8_t DRIVE_RIGHT_AUX        = 20;

inline constexpr std::int8_t DRIVE_LEFT_FRONT       = -13;
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE      = 15;
inline constexpr std::int8_t DRIVE_LEFT_REAR        = -12;
inline constexpr std::int8_t DRIVE_LEFT_AUX         = -11;

// Intake motors (4 total)
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_1  = -10;
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_2  = 1;
inline constexpr std::int8_t INTAKE_TOP_STAGE       = 9;
inline constexpr std::int8_t INTAKE_INDEXER         = 2;

// Pneumatics
inline constexpr std::int8_t PISTON_MATCHLOADER     = 'D';
inline constexpr std::int8_t PISTON_INDEXER         = 'A';
inline constexpr std::int8_t PISTON_WING            = 'C';
inline constexpr std::int8_t PISTON_HOOD            = 'B';

// Sensors
inline constexpr std::int8_t IMU                    = 14;
inline constexpr std::int8_t VERTICAL_ROTATION      = 0;
inline constexpr std::int8_t HORIZONTAL_ROTATION    = 0;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 0;

// Auton selector
inline constexpr std::int8_t LIMIT_SWITCH_SELECT    = 'E';
}  // namespace ports
}  // namespace robot
