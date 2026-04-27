#pragma once

#include "core/config.hpp"

#ifdef ROBOT_BLUE

#include "EZ-Template/util.hpp"
#include <cstdint>

namespace lever {

enum class LeverState { IDLE, SCORE, RETRACT, ZERO };

inline constexpr double SCORE_POSITION = 800.0;
inline constexpr double HOME_POSITION = 0.0;

inline constexpr int LEVER_OUTPUT_MAX      = 127; // SKILLS: 60, MATCH: 127
inline constexpr int LEVER_OUTPUT_AUTON    = 60;
inline constexpr int LEVER_MIDDLE_GOAL_MAX = 80;

inline constexpr double LEVER_PID_KP      = 1.9;
inline constexpr double LEVER_PID_KI      = 0.0;
inline constexpr double LEVER_PID_KD      = 0.16;
inline constexpr double LEVER_PID_START_I = 0.0;
inline constexpr double LEVER_PID_SLOW_KP = 0.6;

inline constexpr int LEVER_EXIT_SMALL_MS = 250;
inline constexpr double LEVER_EXIT_SMALL_DEG = 45.0;
inline constexpr int LEVER_EXIT_BIG_MS = 750;
inline constexpr double LEVER_EXIT_BIG_DEG = 250.0;
inline constexpr int LEVER_EXIT_VEL_MS = 0;
inline constexpr int LEVER_EXIT_MA_MS = 0;

void initialize();
LeverState get_state();
void request_bottom_reset();
ez::exit_output get_pid_exit();
void score_async();
bool score(std::uint32_t timeout_ms = 1200);
void set_pid_default_constants();
void set_pid_slow_constants();

}  // namespace lever

#endif
