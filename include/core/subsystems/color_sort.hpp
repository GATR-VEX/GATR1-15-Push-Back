#pragma once

namespace subsystems::color_sort {

// Color detection hue ranges (tune these based on sensor calibration)
inline constexpr double COLOR_BLUE_HUE_MIN = 0.0;
inline constexpr double COLOR_BLUE_HUE_MAX = 0.0;
inline constexpr double COLOR_RED_HUE_MIN = 0.0;
inline constexpr double COLOR_RED_HUE_MAX = 0.0;
inline constexpr double COLOR_RED_HUE_WRAP_MIN = 0.0;

// Color sort timing
inline constexpr int COLOR_SORT_REVERSE_DELAY_MS = 0;
inline constexpr int COLOR_SORT_RESUME_DELAY_MS = 0;

// Check if detected hue represents a blue ring
bool is_color_blue(double hue);

// Check if detected hue represents a red ring
bool is_color_red(double hue);

// Check if wrong color (opposite of alliance) is detected
bool is_wrong_color_detected();

// Get the current detected hue from the optical sensor
double get_current_hue();

}  // namespace subsystems::color_sort

