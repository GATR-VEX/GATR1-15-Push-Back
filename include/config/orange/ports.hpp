#pragma once

#include <cstdint>

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

// Pneumatics
inline constexpr std::int8_t PISTON_MATCHLOADER_PORT   = 'D';
inline constexpr bool        PISTON_MATCHLOADER_REVERSED = false;
inline constexpr std::int8_t PISTON_INDEXER_PORT       = 'A';
inline constexpr bool        PISTON_INDEXER_REVERSED   = false;
inline constexpr std::int8_t PISTON_WING_PORT          = 'F';
inline constexpr bool        PISTON_WING_REVERSED      = false;
inline constexpr std::int8_t PISTON_HOOD_PORT          = 'B';
inline constexpr bool        PISTON_HOOD_REVERSED      = false;

// Sensors
inline constexpr std::int8_t IMU                    = 21;
inline constexpr std::int8_t VERTICAL_ROTATION      = 0;
inline constexpr std::int8_t HORIZONTAL_ROTATION    = 0;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 3;

// Auton selector
inline constexpr std::int8_t LIMIT_SWITCH_SELECT    = 'E';
}  // namespace ports
}  // namespace robot
