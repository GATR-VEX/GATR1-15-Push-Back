#pragma once

#include <cstdint>

// Timeouts (ms)
inline constexpr std::uint32_t DEFAULT_TIMEOUT_MS   = 5000;  // 5 seconds
inline constexpr std::uint32_t MATCHLOAD_TIMEOUT_MS = 5000;  // 5 seconds

namespace color_sort {

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

// Returns human-readable string of detected color for debug display
const char* get_detected_color_string();

}  // namespace color_sort
