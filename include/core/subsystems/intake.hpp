#pragma once

#include "core/config.hpp"

namespace intake {

/// TODO: Tune these values
// Intake motor speeds
inline constexpr int INTAKE_SPEED = 127;
inline constexpr int INTAKE_SPEED_SLOW = INTAKE_SPEED * 0.65;

// Intake running detection
inline constexpr double INTAKE_VELOCITY_THRESHOLD = 0.0;

#if defined(ROBOT_BLUE)
#include "core/subsystems/intake/intake_states_blue.hpp"
#elif defined(ROBOT_ORANGE)
#include "core/subsystems/intake/intake_states_orange.hpp"
#endif

void initialize();

// Set the target intake state (can be set from driver control or autonomous)
void set_target_state(IntakeState state);

// Get the current target intake state
IntakeState get_target_state();

// Set power for bottom intake motors (2 motors - initial intake stage)
void set_bottom_power(int power);

// Set power for top stage motor
void set_top_power(int power);

// Check if intake motors are currently running (velocity > threshold)
bool is_running();

// Get driver input state
IntakeState get_driver_state();

// Apply intake state to motors
void apply_state(IntakeState state);

// Convenience functions for autonomous and driver control
#if defined(ROBOT_BLUE)
void stop();
void fast();
void slow();
void reverse();
#elif defined(ROBOT_ORANGE)
void stop();
void collect();
void score_long();
void score_slow();
void score_middle();
void score_middle_fast();
void reverse();
void reverse_slow();
#endif

}  // namespace intake
