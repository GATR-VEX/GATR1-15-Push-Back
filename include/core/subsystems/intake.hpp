#pragma once

#include "core/config.hpp"

namespace intake {
inline constexpr int INTAKE_SPEED = 127;
inline constexpr int INTAKE_SPEED_SLOW = INTAKE_SPEED * 0.65;

// Intake running detection
inline constexpr double INTAKE_VELOCITY_THRESHOLD = 0.0;

#if defined(ROBOT_BLUE)
enum class IntakeState { STOP, FAST, SLOW, REVERSE, REVERSE_SLOW };
#elif defined(ROBOT_ORANGE)
enum class IntakeState { STOP, COLLECT, SCORE, SCORE_SLOW, REVERSE, REVERSE_SLOW };
#else
#error "No robot defined! Define ROBOT_BLUE or ROBOT_ORANGE."
#endif

void initialize();

// Set the target intake state (can be set from driver control or autonomous)
void set_target_state(IntakeState state);

// Get the current target intake state
IntakeState get_target_state();

// Check if intake motors are currently running (velocity > threshold)
bool is_running();

// Get driver input state
IntakeState get_driver_state();

// Apply intake state to motors
void apply_state(IntakeState state);

#if defined(ROBOT_BLUE)
// After driver/auton resolution: may force final_state to STOP (e.g. when lever is active).
void check_lever_override(IntakeState& final_state);
#endif

// Convenience functions for autonomous and driver control
#if defined(ROBOT_BLUE)
void stop();
void fast();
void slow();
void reverse();
void reverse_slow();
#elif defined(ROBOT_ORANGE)
void stop();
void collect();
void score();
void score_slow();
void reverse();
void reverse_slow();
#else
#error "No robot defined! Define ROBOT_BLUE or ROBOT_ORANGE."
#endif

}  // namespace intake
