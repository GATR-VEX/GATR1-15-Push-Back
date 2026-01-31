#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <cmath>
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
    globals::intake_bottom_stage.move(power);
}

void set_top_power(int power) {
    globals::intake_top_stage.move(power);
}

void set_indexer_power(int power) {
    globals::intake_indexer.move(power);
}

bool is_running() {
    return std::abs(globals::intake_bottom_stage.get_actual_velocity()) > INTAKE_VELOCITY_THRESHOLD;
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
            set_top_power(0);
            set_indexer_power(0);
            indexer->retract();
            break;

        case IntakeState::SCORE_LONG:
            set_bottom_power(INTAKE_SPEED);
            set_top_power(INTAKE_SPEED);
            set_indexer_power(INTAKE_SPEED);
            indexer->retract();
            break;

        case IntakeState::SCORE_SLOW:
            set_bottom_power(INTAKE_SPEED_SLOW);
            set_top_power(INTAKE_SPEED_SLOW);
            set_indexer_power(INTAKE_SPEED_SLOW);
            indexer->retract();
            break;

        case IntakeState::SCORE_MIDDLE:
            set_bottom_power(INTAKE_SPEED);
            set_top_power(INTAKE_SPEED);
            set_indexer_power(-INTAKE_SPEED);
            indexer->extend();
            break;

        case IntakeState::COLLECT:
            set_bottom_power(INTAKE_SPEED);
            set_top_power(0);
            set_indexer_power(0);
            indexer->retract();
            break;

        case IntakeState::REVERSE:
            set_bottom_power(-INTAKE_SPEED);
            set_top_power(-INTAKE_SPEED);
            set_indexer_power(-INTAKE_SPEED);
            indexer->retract();
            break;
    }
}

// Convenience functions for autonomous
void stop() { target_state = IntakeState::STOP; }

void collect() { target_state = IntakeState::COLLECT; }

void score_long() { target_state = IntakeState::SCORE_LONG; }

void score_slow() { target_state = IntakeState::SCORE_SLOW; }

void score_middle() { target_state = IntakeState::SCORE_MIDDLE; }

void reverse() { target_state = IntakeState::REVERSE; }

}  // namespace subsystems::intake
