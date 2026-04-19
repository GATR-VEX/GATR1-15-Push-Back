#pragma once

#include "core/config.hpp"

#ifdef ROBOT_BLUE

#include "EZ-Template/util.hpp"

namespace lever {

enum class LeverState { IDLE, SCORE, RETRACT, ZERO };

inline constexpr double SCORE_POSITION = 770.0;
inline constexpr double HOME_POSITION = 0.0;

inline constexpr int LEVER_OUTPUT_MAX = 127;
inline constexpr int LEVER_MIDDLE_GOAL_MAX = 80;

void initialize();
LeverState get_state();
void request_bottom_reset();
ez::exit_output get_pid_exit();

}  // namespace lever

#endif
