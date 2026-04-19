#pragma once

#include <cstdint>

namespace robot {
namespace ports {
// Drive motors (8 total)
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE      = 1;
inline constexpr std::int8_t DRIVE_LEFT_AUX         = -2;
inline constexpr std::int8_t DRIVE_LEFT_REAR        = 3;
inline constexpr std::int8_t DRIVE_LEFT_FRONT       = 4;

inline constexpr std::int8_t DRIVE_RIGHT_FRONT      = -5;
inline constexpr std::int8_t DRIVE_RIGHT_AUX        = 6;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE     = -9;
inline constexpr std::int8_t DRIVE_RIGHT_REAR       = -10;

// Intake motors (negative port = reversed)
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_1  = -18;
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_2  = 15;
inline constexpr std::int8_t INTAKE_TOP_STAGE       = 14;

// Pneumatics
inline constexpr std::int8_t PISTON_MATCHLOADER_PORT     = 0;
inline constexpr bool        PISTON_MATCHLOADER_REVERSED = false;
inline constexpr std::int8_t PISTON_INTAKE_PORT          = 0;
inline constexpr bool        PISTON_INTAKE_REVERSED      = false;
inline constexpr std::int8_t PISTON_WING_PORT            = 0;
inline constexpr bool        PISTON_WING_REVERSED        = false;
inline constexpr std::int8_t PISTON_GATE_PORT            = 0;
inline constexpr bool        PISTON_GATE_REVERSED        = false;
inline constexpr std::int8_t PISTON_FOUR_BAR_PORT        = 0;
inline constexpr bool        PISTON_FOUR_BAR_REVERSED    = false;

// Sensors
inline constexpr std::int8_t IMU                    = 8;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 0;

// Auton selector
inline constexpr std::int8_t LIMIT_SWITCH_SELECT    = 'D';
}  // namespace ports
}  // namespace robot
