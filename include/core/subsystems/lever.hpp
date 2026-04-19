#pragma once

#include "core/config.hpp"

#ifdef ROBOT_BLUE

namespace lever {

enum class LeverState { IDLE, ACTIVE };

inline constexpr double SCORE_POSITION_DEG = 770.0;
inline constexpr double HOME_POSITION_DEG = 0.0;
inline constexpr double STOW_EPS_DEG = 20.0;

inline constexpr double HOMING_TARGET_DEG = -200.0;

void initialize();
LeverState get_state();
void request_bottom_reset();

}  // namespace lever

#endif
