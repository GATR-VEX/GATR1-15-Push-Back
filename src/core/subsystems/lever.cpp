#include "core/subsystems/lever.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include "EZ-Template/api.hpp"

#include <algorithm>
#include <memory>

#include "pros/rtos.hpp"

#ifdef ROBOT_BLUE

namespace lever {

static LeverState state = LeverState::IDLE;

static ez::PID lever{0.9, 0.0, 0.16, 0.0, "Lever"};

namespace {

std::unique_ptr<pros::Task> lever_task;

void apply_lever_state(LeverState s) {
    const double pos = globals::lever_motor.get_position();

    switch (s) {
        case LeverState::IDLE:
            globals::lever_motor.move(0);
            pistons::safe_retract(pistons::gate);
            break;

        case LeverState::SCORE: {
            lever.target_set(SCORE_POSITION);
            pistons::safe_extend(pistons::gate);

            // when four-bar is down, use the middle goal max
            int max_out = pistons::four_bar->is_extended() 
                ? LEVER_OUTPUT_MAX : LEVER_MIDDLE_GOAL_MAX;

            globals::lever_motor.move(lever.compute(pos));
            break;
        }

        case LeverState::RETRACT: {
            lever.target_set(HOME_POSITION);
            pistons::safe_retract(pistons::gate);

            // clamp the output to the max, only negative output
            int output = std::clamp(lever.compute(pos), -double(LEVER_OUTPUT_MAX), 0.0);
            globals::lever_motor.move(output);
            break;
        }

        case LeverState::ZERO:
            // TODO: some homing func hardcoded
            // needs to not change zero pos by a lot
            break;
    }
}

static bool retract_complete() {
    return lever.exit_condition() != ez::RUNNING;
}

static void lever_controller_task() {
    while (true) {
        const bool held = robot::controller.get_digital(robot::Controls::lever);

        apply_lever_state(state);

        switch (state) {
            case LeverState::IDLE:
                if (held) {
                    state = LeverState::SCORE;
                }
                break;

            case LeverState::SCORE:
                if (!held) {
                    state = LeverState::RETRACT;
                }
                break;

            case LeverState::RETRACT:
                if (held) {
                    state = LeverState::SCORE;
                } else if (retract_complete()) {
                    state = LeverState::ZERO;
                }
                break;

            case LeverState::ZERO:
                state = LeverState::IDLE;
                break;
        }

        pros::delay(core::util::DELAY_TIME);
    }
}

}  // namespace

LeverState get_state() {
    return state;
}

ez::exit_output get_pid_exit() {
    if (state == LeverState::IDLE) {
        return ez::RUNNING;
    }
    return lever.exit_condition();
}

void request_bottom_reset() {}

void initialize() {
    lever.exit_condition_set(500, 8.0, 0, 0, 80, 800);
    lever_task = std::make_unique<pros::Task>(lever_controller_task);
}

}  // namespace lever

#endif
