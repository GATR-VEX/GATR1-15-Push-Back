#pragma once

#include <cstdint>
#include <tuple>
#include <utility>

namespace robot {
namespace ports {
// Drive motors (8 total)
inline constexpr std::int8_t DRIVE_RIGHT_FRONT      = -18;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE     = 17;
inline constexpr std::int8_t DRIVE_RIGHT_REAR       = 19;
inline constexpr std::int8_t DRIVE_RIGHT_AUX        = 20;

inline constexpr std::int8_t DRIVE_LEFT_FRONT       = 15;
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE      = -13;
inline constexpr std::int8_t DRIVE_LEFT_REAR        = -12;
inline constexpr std::int8_t DRIVE_LEFT_AUX         = -11;

// Intake motors (4 total)
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_1  = -10;
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_2  = 1;
inline constexpr std::int8_t INTAKE_TOP_STAGE       = 9;
inline constexpr std::int8_t INTAKE_INDEXER         = 2;

// Pneumatics (port, reversed, default_extended — released state in HOLD mode)
inline constexpr std::tuple<std::int8_t, bool, bool> PISTON_MATCHLOADER = {'D', false, false};
inline constexpr std::tuple<std::int8_t, bool, bool> PISTON_INDEXER     = {'A', false, false};
inline constexpr std::tuple<std::int8_t, bool, bool> PISTON_WING        = {'F', false, true};
inline constexpr std::tuple<std::int8_t, bool, bool> PISTON_HOOD        = {'B', false, false};

// Sensors
inline constexpr std::int8_t IMU                    = 21;
inline constexpr std::int8_t VERTICAL_ROTATION      = 0;
inline constexpr std::int8_t HORIZONTAL_ROTATION    = 0;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 3;

// Auton selector
inline constexpr std::int8_t LIMIT_SWITCH_SELECT    = 'E';
}  // namespace ports
}  // namespace robot
