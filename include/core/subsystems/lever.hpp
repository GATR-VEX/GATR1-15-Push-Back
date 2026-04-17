#pragma once

#include <cstdint>

#include "core/config.hpp"

#ifdef ROBOT_BLUE

namespace lever {

enum class LeverState {
    IDLE,
    SCORE,
    SCORE_SLOW,
    RETURN,
    ZERO
};

inline constexpr int SCORE_POWER = 127;
inline constexpr int SCORE_SLOW_POWER = 80;
inline constexpr int RETURN_POWER = -127;
inline constexpr double RETURN_IDLE_POSITION_EPS = 5.0;
inline constexpr bool USE_SCORE_SLOW_BY_POSITION = false;
inline constexpr double SCORE_SLOW_AT_POSITION = 0.0;

void initialize();
void request_zero();
LeverState get_state();

}  // namespace lever

#endif