#pragma once

#include <cstdint>

// Timeouts (ms)
inline constexpr std::uint32_t DEFAULT_TIMEOUT_MS     = 5000;   // 5 seconds
inline constexpr std::uint32_t MATCHLOAD_TIMEOUT_MS   = 5000;   // 5 seconds
inline constexpr std::uint32_t LONG_GRACE_TIMEOUT_MS  = 5000;   // 5 seconds
inline constexpr std::uint32_t SHORT_GRACE_TIMEOUT_MS = 500;    // 0.5 seconds

namespace subsystems::color_sort {

enum class Color {
    RED,
    BLUE
};

// Hue ranges for color detection (tune these based on sensor calibration)
inline constexpr double BLUE_HUE_MIN = 150.0;
inline constexpr double BLUE_HUE_MAX = 249.0;

inline constexpr double RED_HUE_MIN  = 0.0;
inline constexpr double RED_HUE_MAX  = 30.0;
inline constexpr double RED_HUE_WRAP = 340.0;  // Red wraps around 360

// Ball presence detection (optical proximity 0-255, tune for your setup)
inline constexpr std::int32_t BALL_PROXIMITY_THRESHOLD = 50;

// Get the current detected hue from the optical sensor
double get_hue();

// Check if the current hue matches the specified color
bool is_color(Color color);

// Wait until the sensor detects the specified color
// Returns true if color was detected, false if timeout occurred
bool wait_for_color(Color color, std::uint32_t timeout_ms = DEFAULT_TIMEOUT_MS);

// Ball presence detection (uses optical proximity - tune threshold for your setup)
// Returns true if a ball appears to be in range of the optical sensor
bool is_ball_in_intake();

// Wait until a ball is detected, or timeout. Returns true if ball detected, false if timeout.
bool wait_for_ball(std::uint32_t timeout_ms = DEFAULT_TIMEOUT_MS);

// Grace periods for wait_until_balls_scored
inline constexpr std::uint32_t WAIT_BALLS_LONG_GRACE_MS  = LONG_GRACE_TIMEOUT_MS;
inline constexpr std::uint32_t WAIT_BALLS_SHORT_GRACE_MS = SHORT_GRACE_TIMEOUT_MS;

// Wait until no balls detected for grace period. Uses long grace initially; after scoring
// for longer than long_grace, switches to short grace (last ball likely just cleared).
void wait_until_balls_scored(std::uint32_t long_grace_ms = WAIT_BALLS_LONG_GRACE_MS,
                             std::uint32_t short_grace_ms = WAIT_BALLS_SHORT_GRACE_MS);

// Returns human-readable string of detected color for debug display
const char* get_detected_color_string();

}  // namespace subsystems::color_sort
