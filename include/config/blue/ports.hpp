#pragma once

#include <cstdint>
#include <utility>

namespace robot {
namespace ports {
// Drive motors (8 total)
inline constexpr std::int8_t DRIVE_RIGHT_FRONT      = 7;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE     = -8;
inline constexpr std::int8_t DRIVE_RIGHT_REAR       = 9;
inline constexpr std::int8_t DRIVE_RIGHT_AUX        = 20;

inline constexpr std::int8_t DRIVE_LEFT_FRONT       = -2;
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE      = 5;
inline constexpr std::int8_t DRIVE_LEFT_REAR        = -3;
inline constexpr std::int8_t DRIVE_LEFT_AUX         = -11;

// Intake motors (4 total)
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_1  = 1;
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_2  = -10;
inline constexpr std::int8_t INTAKE_TOP_STAGE       = 19;
inline constexpr std::int8_t INTAKE_INDEXER         = 12;

// Pneumatics (port, reversed)
inline constexpr std::pair<std::int8_t, bool> PISTON_MATCHLOADER = {'A', false};
inline constexpr std::pair<std::int8_t, bool> PISTON_INDEXER     = {'B', false};
inline constexpr std::pair<std::int8_t, bool> PISTON_WING        = {'C', false};

// Sensors
inline constexpr std::int8_t IMU                    = 18;
inline constexpr std::int8_t VERTICAL_ROTATION      = 0;
inline constexpr std::int8_t HORIZONTAL_ROTATION    = 0;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 14;

// Auton selector
inline constexpr std::int8_t LIMIT_SWITCH_SELECT    = 'E';
}  // namespace ports
}  // namespace robot
