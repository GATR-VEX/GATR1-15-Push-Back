#pragma once

#include <cstdint>

namespace robot {
namespace ports {
// Drive motors (8 total)
inline constexpr std::int8_t DRIVE_RIGHT_FRONT      = 19;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE     = -16;
inline constexpr std::int8_t DRIVE_RIGHT_REAR       = 12;
inline constexpr std::int8_t DRIVE_RIGHT_AUX        = 14;

inline constexpr std::int8_t DRIVE_LEFT_FRONT       = -18;
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE      = 15;
inline constexpr std::int8_t DRIVE_LEFT_REAR        = -11;
inline constexpr std::int8_t DRIVE_LEFT_AUX         = -13;

// Intake motors
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_1  = -4;
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_2  = 3;

// Lever motors
inline constexpr std::int8_t LEVER_LEFT  = 5;
inline constexpr std::int8_t LEVER_RIGHT = 2;

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
inline constexpr std::int8_t IMU                    = 1;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 0;
inline constexpr std::int8_t RADIO                  = 17;

// Auton selector
inline constexpr std::int8_t LIMIT_SWITCH_SELECT    = 'D';
}  // namespace ports
}  // namespace robot
