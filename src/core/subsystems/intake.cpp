#include "core/subsystems/intake.hpp"
#include "core/subsystems/color_sort.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <memory>

#include "pros/motors.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

namespace subsystems::intake {

std::unique_ptr<pros::Task> intake_task;

// Target state that can be set globally
static IntakeState target_state = IntakeState::STOP;

void intake_controller_task() {
    while (true) {

        // collect autonomous requested states
        IntakeState final_state = target_state;

        // Get driver input if in driver control mode
        if (!pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
            final_state = get_driver_state();
        }

        // Color sort logic (overrides driver input)
        // if (color_sort::is_wrong_color_detected() && intake::is_running()){
        //     final_state = IntakeState::EJECT;
        // }

        // send state to motors
        apply_state(final_state);

        // Small delay to prevent the task from consuming too much CPU
        pros::delay(core::util::DELAY_TIME);
    }
}

void initialize() {
    intake_task = std::make_unique<pros::Task>(intake_controller_task);
}

void set_bottom_power(int power) {
    globals::intake_stage_motors.move(power);
}

void set_indexer_power(int power) {
    globals::intake_indexer_motor.move(power);
}

bool is_running() {
    // Check if intake motors are actually moving
    // This is useful for color sort logic - you need to know if the intake
    // is literally moving and should be moving to eject a wrong-color ball
    //
    // Steps to implement:
    // 1. Get the actual velocity of the bottom intake motors:
    //    - Use: globals::intake_stage_motors.get_actual_velocity()
    // 2. Compare to the threshold:
    //    - If velocity is greater than INTAKE_VELOCITY_THRESHOLD, motors are running
    // 3. Return true if motors are running, false otherwise

    return false;  // TODO: Implement velocity check
}

IntakeState get_driver_state() {
    // Priority order: score buttons > intake > reverse > stop
    if (robot::controller.get_digital(robot::Controls::score_long_goal)) {
        return IntakeState::SCORE_LONG;
    } else if (robot::controller.get_digital(robot::Controls::score_middle_goal)) {
        return IntakeState::SCORE_MIDDLE;
    } else if (robot::controller.get_digital(robot::Controls::intake)) {
        return IntakeState::COLLECT;
    } else if (robot::controller.get_digital(robot::Controls::reverse)) {
        return IntakeState::REVERSE;
    } else {
        return IntakeState::STOP;
    }
}

void apply_state(IntakeState state) {
    switch (state) {
        case IntakeState::STOP:
            set_bottom_power(0);
            set_indexer_power(0);
            break;

        case IntakeState::SCORE_LONG:
            set_bottom_power(INTAKE_SPEED);
            set_indexer_power(INTAKE_SPEED);
            break;

        case IntakeState::SCORE_MIDDLE:
            set_bottom_power(INTAKE_SPEED);
            set_indexer_power(-INTAKE_SPEED);
            break;

        case IntakeState::COLLECT:
            set_bottom_power(INTAKE_SPEED);
            set_indexer_power(INTAKE_SPEED);
            break;

        case IntakeState::REVERSE:
            set_bottom_power(-INTAKE_SPEED);
            set_indexer_power(-INTAKE_SPEED);
            break;

        case IntakeState::EJECT:
            set_bottom_power(OUTTAKE_SPEED);
            set_indexer_power(-OUTTAKE_SPEED);
            // TODO: Add color sort piston control
            // robot::subsystems::pistons::color_sort.extend();
            // pros::delay(color_sort::COLOR_SORT_REVERSE_DELAY_MS);
            // robot::subsystems::pistons::color_sort.retract();
            break;
    }
}

// Convenience functions for autonomous
void stop() { target_state = IntakeState::STOP; }

void collect() { target_state = IntakeState::COLLECT; }

void score_long() { target_state = IntakeState::SCORE_LONG; }

void score_middle() { target_state = IntakeState::SCORE_MIDDLE; }

void reverse() { target_state = IntakeState::REVERSE; }

}  // namespace subsystems::intake
