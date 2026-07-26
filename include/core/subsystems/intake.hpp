/**
 * @file intake.hpp
 * @brief Intake state machine API (robot-specific states and helpers).
 *
 * A background task in intake.cpp merges autonomous set_target_state() calls
 * with driver input during opcontrol. Robot-specific apply_state() and button
 * mappings live in intake_blue.cpp and intake_orange.cpp.
 */

#pragma once

#include "core/config.hpp"

namespace intake {
#if defined(ROBOT_BLUE)
inline constexpr int INTAKE_SPEED         = 127;
inline constexpr int INTAKE_SPEED_SLOW    = 80;
inline constexpr int INTAKE_REVERSE_SPEED = 50;
#elif defined(ROBOT_ORANGE)
inline constexpr int INTAKE_SPEED         = 127;
inline constexpr int INTAKE_SPEED_SLOW    = 80;
inline constexpr int INTAKE_REVERSE_SPEED = 50;
#endif

inline constexpr double INTAKE_VELOCITY_THRESHOLD = 0.0;

#if defined(ROBOT_BLUE)
enum class IntakeState { STOP, FAST, SLOW, REVERSE, REVERSE_SLOW };
#elif defined(ROBOT_ORANGE)
enum class IntakeState { STOP, COLLECT, SCORE_LONG, SCORE_MIDDLE, REVERSE, REVERSE_SLOW };
#endif

void initialize();
void set_target_state(IntakeState state);
IntakeState get_target_state();
IntakeState get_state();
bool is_running();

/** Override final_state from controller buttons. */
void apply_driver_input(IntakeState& final_state);

/** Drive motors and related pistons for the given state. */
void apply_state(IntakeState state);

#if defined(ROBOT_BLUE)
/** Force STOP while the lever FSM is active. */
void check_lever_override(IntakeState& final_state);
#endif

#if defined(ROBOT_BLUE)
void stop();
void fast();
void slow();
void reverse();
void reverse_slow();
#elif defined(ROBOT_ORANGE)
void stop();
void collect();
void score_long();
void score_middle();
void reverse();
void reverse_slow();
#endif

}  // namespace intake
