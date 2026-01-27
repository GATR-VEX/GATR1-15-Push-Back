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

// Intake motors (4 total)
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_1  = 0;
inline constexpr std::int8_t INTAKE_BOTTOM_STAGE_2  = 0;
inline constexpr std::int8_t INTAKE_TOP_STAGE       = 0;
inline constexpr std::int8_t INTAKE_INDEXER         = 0;

// Pneumatics
inline constexpr std::int8_t PISTON_MATCHLOADER     = 0;
inline constexpr std::int8_t PISTON_INDEXER         = 0;
inline constexpr std::int8_t PISTON_WING            = 0;
inline constexpr std::int8_t PISTON_HOOD            = 0;

// Sensors
inline constexpr std::int8_t IMU                    = 0;
inline constexpr std::int8_t VERTICAL_ROTATION      = 0;
inline constexpr std::int8_t HORIZONTAL_ROTATION    = 0;
inline constexpr std::int8_t OPTICAL_COLOR_SORT     = 0;
}  // namespace ports
}  // namespace robot
