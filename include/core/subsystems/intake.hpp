#pragma once

namespace subsystems::intake {

/// TODO: Tune these values
// Intake motor speeds
inline constexpr int INTAKE_SPEED = 127;
inline constexpr int INTAKE_SPEED_SLOW = 100;

// Intake running detection
inline constexpr double INTAKE_VELOCITY_THRESHOLD = 0.0;

enum class IntakeState {
    STOP,
    SCORE_LONG,
    SCORE_MIDDLE,
    COLLECT,
    REVERSE
};

void initialize();

// Set the target intake state (can be set from driver control or autonomous)
void set_target_state(IntakeState state);

// Get the current target intake state
IntakeState get_target_state();

// Set power for bottom intake motors (2 motors - initial intake stage)
void set_bottom_power(int power);

// Set power for top stage motor
void set_top_power(int power);

// Set power for indexer motor (final stage - scores into goals)
void set_indexer_power(int power);

// Check if intake motors are currently running (velocity > threshold)
bool is_running();

// Get driver input state
IntakeState get_driver_state();

// Apply intake state to motors
void apply_state(IntakeState state);

// Convenience functions for autonomous and driver control
// These provide a cleaner API than set_target_state(IntakeState::...)
void stop();         // Stop all intake motors
void collect();      // Start collecting balls
void score_long();   // Score into long goal
void score_middle(); // Score into middle goal
void reverse();      // Reverse all motors (outtake)

}  // namespace subsystems::intake
