/**
 * @file color_sort.hpp
 * @brief Optical sensor helpers for alliance color and ball detection.
 */

#pragma once

#include <cstdint>

inline constexpr std::uint32_t DEFAULT_TIMEOUT_MS   = 5000;
inline constexpr std::uint32_t MATCHLOAD_TIMEOUT_MS = 5000;

namespace color_sort {

enum class Color {
    RED,
    BLUE
};

/** Hue window for blue balls (degrees, 0–360). */
inline constexpr double BLUE_HUE_MIN = 150.0;
inline constexpr double BLUE_HUE_MAX = 249.0;

/** Red wraps past 360; check [RED_HUE_WRAP, 360) and [0, RED_HUE_MAX]. */
inline constexpr double RED_HUE_MIN  = 0.0;
inline constexpr double RED_HUE_MAX  = 30.0;
inline constexpr double RED_HUE_WRAP = 340.0;

/** Optical proximity threshold (0–255) for ball-in-intake detection. */
inline constexpr std::int32_t BALL_PROXIMITY_THRESHOLD = 50;

double get_hue();
bool is_color(Color color);

/** Poll until color detected or timeout. @return true if color seen before timeout */
bool wait_for_color(Color color, std::uint32_t timeout_ms = DEFAULT_TIMEOUT_MS);

bool is_ball_in_intake();
bool wait_for_ball(std::uint32_t timeout_ms = DEFAULT_TIMEOUT_MS);

/** "RED", "BLUE", or "none" for LCD debug. */
const char* get_detected_color_string();

}  // namespace color_sort
