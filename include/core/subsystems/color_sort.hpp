#pragma once

#include <cstdint>

namespace subsystems::color_sort {

enum class Color {
    RED,
    BLUE
};

// Default timeout for wait functions (ms)
inline constexpr std::uint32_t DEFAULT_TIMEOUT_MS = 5000;

// Hue ranges for color detection (tune these based on sensor calibration)
inline constexpr double BLUE_HUE_MIN = 200.0;
inline constexpr double BLUE_HUE_MAX = 240.0;

inline constexpr double RED_HUE_MIN  = 0.0;
inline constexpr double RED_HUE_MAX  = 20.0;
inline constexpr double RED_HUE_WRAP = 340.0;  // Red wraps around 360

// Get the current detected hue from the optical sensor
double get_hue();

// Check if the current hue matches the specified color
bool is_color(Color color);

// Wait until the sensor detects the specified color
// Returns true if color was detected, false if timeout occurred
bool wait_for_color(Color color, std::uint32_t timeout_ms = DEFAULT_TIMEOUT_MS);

}  // namespace subsystems::color_sort
