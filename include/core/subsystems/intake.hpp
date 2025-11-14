#pragma once

namespace subsystems::intake {
/// TODO: Tune these values
// Intake motor speeds
inline constexpr int INTAKE_SPEED = 127;
inline constexpr int INTAKE_SPEED_SLOW = 100;
inline constexpr int OUTTAKE_SPEED = -127;

// Color detection hue ranges (tune these based on sensor calibration)
inline constexpr double COLOR_BLUE_HUE_MIN = 0.0;
inline constexpr double COLOR_BLUE_HUE_MAX = 0.0;
inline constexpr double COLOR_RED_HUE_MIN = 0.0;
inline constexpr double COLOR_RED_HUE_MAX = 0.0;
inline constexpr double COLOR_RED_HUE_WRAP_MIN = 0.0;

// Intake running detection
inline constexpr double INTAKE_VELOCITY_THRESHOLD = 0.0; 

// Color sort timing
inline constexpr int COLOR_SORT_REVERSE_DELAY_MS = 0; 
inline constexpr int COLOR_SORT_RESUME_DELAY_MS = 0;

void initialize();

// Set power for bottom/middle stage intake (2 motors)
void set_stage_power(int power);

// Set power for indexer motor (between middle and long goal)
void set_indexer_power(int power);

// Set power for long goal rollers (2 motors)
void set_rollers_power(int power);

// Check if intake motors are currently running (velocity > threshold)
bool is_running();

// Check if detected hue represents a blue ring
bool is_color_blue(double hue);

// Check if detected hue represents a red ring
bool is_color_red(double hue);

// Check if wrong color (opposite of alliance) is detected
bool is_wrong_color_detected();

}  // namespace subsystems::intake
