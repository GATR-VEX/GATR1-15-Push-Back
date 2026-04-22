#pragma once

#include "core/config.hpp"

#ifdef ROBOT_BLUE

#include "EZ-Template/util.hpp"

namespace lever {

enum class LeverState { IDLE, SCORE, RETRACT, ZERO };

inline constexpr double SCORE_POSITION = 800.0;
inline constexpr double HOME_POSITION = 0.0;

inline constexpr int LEVER_OUTPUT_MAX = 127;
inline constexpr int LEVER_MIDDLE_GOAL_MAX = 80;

inline constexpr double LEVER_PID_KP = 0.9;
inline constexpr double LEVER_PID_KI = 0.0;
inline constexpr double LEVER_PID_KD = 0.16;
inline constexpr double LEVER_PID_START_I = 0.0;

inline constexpr int LEVER_EXIT_SMALL_MS = 250;
inline constexpr double LEVER_EXIT_SMALL_DEG = 12.0;
inline constexpr int LEVER_EXIT_BIG_MS = 0;
inline constexpr double LEVER_EXIT_BIG_DEG = 0.0;
inline constexpr int LEVER_EXIT_VEL_MS = 0;
inline constexpr int LEVER_EXIT_MA_MS = 0;

void initialize();
LeverState get_state();
void request_bottom_reset();
ez::exit_output get_pid_exit();

}  // namespace lever

#endif
