#pragma once

#include <cstdint>

namespace robot {
namespace ports {
// Drive motors (8 total)
inline constexpr std::int8_t DRIVE_RIGHT_FRONT      = 0;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE     = 0;
inline constexpr std::int8_t DRIVE_RIGHT_REAR       = 0;
inline constexpr std::int8_t DRIVE_RIGHT_AUX        = 0;

inline constexpr std::int8_t DRIVE_LEFT_FRONT       = 0;
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE      = 0;
inline constexpr std::int8_t DRIVE_LEFT_REAR        = 0;
inline constexpr std::int8_t DRIVE_LEFT_AUX         = 0;

// Intake motors
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_1  = 0;
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_2  = 0;

// Lever motors
inline constexpr std::int8_t LEVER_LEFT  = 0;
inline constexpr std::int8_t LEVER_RIGHT = 0;


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
inline constexpr std::int8_t IMU                    = 0;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 0;

// Auton selector
inline constexpr std::int8_t LIMIT_SWITCH_SELECT    = 'D';
}  // namespace ports
}  // namespace robot
