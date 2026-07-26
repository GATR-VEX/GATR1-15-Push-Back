/**
 * @file intake.cpp
 * @brief Intake background task: merges auton target with driver input.
 */

#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <cmath>
#include <memory>
#include <type_traits>

#include "pros/motors.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

namespace intake {

std::unique_ptr<pros::Task> intake_task;

// Target state that can be set globally
static IntakeState target_state = IntakeState::STOP;
static IntakeState current_state = IntakeState::STOP;

void intake_controller_task() {
    while (true) {
        // Collect autonomous requested states
        IntakeState final_state = target_state;

        // Get driver input if in driver control mode
        if (!pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
            apply_driver_input(final_state);
        }

#ifdef ROBOT_BLUE
        // Allow lever to disable intake if in motion
        check_lever_override(final_state);
#endif

        // send state to motors
        current_state = final_state;
        apply_state(final_state);

        // Small delay to prevent the task from consuming too much CPU
        pros::delay(core::util::DELAY_TIME);
    }
}

void initialize() {
    intake_task = std::make_unique<pros::Task>(intake_controller_task);
}

void set_target_state(IntakeState state) {
    target_state = state;
}

IntakeState get_target_state() {
    return target_state;
}

IntakeState get_state() {
    return current_state;
}

bool is_running() {
    return std::abs(globals::intake_bottom_stage.get_actual_velocity()) > INTAKE_VELOCITY_THRESHOLD;
}

}  // namespace intake
