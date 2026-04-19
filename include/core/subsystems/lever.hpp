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

/** EZ settle: within `small_error` deg for `small_exit_time` ms (and velocity gate). Tune on-robot. */
inline constexpr int LEVER_PID_EXIT_SMALL_TIME_MS = 800;
inline constexpr double LEVER_PID_EXIT_SMALL_ERROR_DEG = 20.0;
inline constexpr int LEVER_PID_EXIT_VEL_TIME_MS = 150;
inline constexpr int LEVER_PID_EXIT_MA_TIMEOUT_MS = 800;

/** Snapshot from last lever control tick (safe to read from screen task). */
struct ExitDebugSnapshot {
    ez::exit_output exit_kind{ez::RUNNING};
    double target_deg{0};
    double error_deg{0};
    double pid_output{0};
    int small_exit_ms{0};
    double small_error_deg{0};
    int big_exit_ms{0};
    double big_error_deg{0};
    int velocity_exit_ms{0};
};

void initialize();
LeverState get_state();
void request_bottom_reset();
ez::exit_output get_pid_exit();
ExitDebugSnapshot get_exit_debug();

}  // namespace lever

#endif
