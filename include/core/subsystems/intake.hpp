#pragma once

#include "core/config.hpp"

namespace intake {
#if defined(ROBOT_BLUE)
inline constexpr int INTAKE_SPEED = 127;
inline constexpr int INTAKE_SPEED_SLOW = static_cast<int>(INTAKE_SPEED * 0.65);
#elif defined(ROBOT_ORANGE)
inline constexpr int INTAKE_SPEED = 127;
inline constexpr int INTAKE_SPEED_SLOW = static_cast<int>(INTAKE_SPEED * 0.65);
#endif

// Intake running detection
inline constexpr double INTAKE_VELOCITY_THRESHOLD = 0.0;

#if defined(ROBOT_BLUE)
enum class IntakeState { STOP, FAST, SLOW, REVERSE, REVERSE_SLOW };
#elif defined(ROBOT_ORANGE)
enum class IntakeState { STOP, COLLECT, SCORE, SCORE_SLOW, REVERSE, REVERSE_SLOW };
#endif

void initialize();

void set_target_state(IntakeState state);
IntakeState get_target_state();
bool is_running();
void apply_driver_input(IntakeState& final_state);
void apply_state(IntakeState state);

#if defined(ROBOT_BLUE)
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
void score();
void score_slow();
void reverse();
void reverse_slow();
#endif

}  // namespace intake
