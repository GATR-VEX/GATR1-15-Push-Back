#pragma once

#include <cstdint>

namespace subsystems::comp_timer {

inline constexpr std::uint32_t DRIVER_CONTROL_TIME_MS  = 90000;  // 90 seconds
inline constexpr std::uint32_t WARNING_20S_MS          = 20000;  // 20 seconds remaining
inline constexpr std::uint32_t COUNTDOWN_START_MS      = 10000;  // 10 seconds remaining
inline constexpr std::uint32_t FINAL_COUNTDOWN_MS      = 3000;   // Last 3 seconds

void initialize();

void update();

}  // namespace subsystems::comp_timer
