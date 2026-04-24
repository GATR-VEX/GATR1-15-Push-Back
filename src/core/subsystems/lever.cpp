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
static ez::exit_output last_exit{ez::RUNNING};
static ez::PID lever{LEVER_PID_KP, LEVER_PID_KI, LEVER_PID_KD, LEVER_PID_START_I, "Lever"};
static bool req_async = false;

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

            int output = std::clamp(lever.compute(pos), 0.0, double(max_out));
            globals::lever_motor.move(output);
            break;
        }

        case LeverState::RETRACT: {
            lever.target_set(HOME_POSITION);
            pistons::safe_retract(pistons::gate);

            // clamp the output to the max, only negative output
            int output = std::clamp(lever.compute(pos), -double(MAX_SPEED), 0.0);
            globals::lever_motor.move(output);
            break;
        }

        case LeverState::ZERO:
            // Some homing function could be added here if desired
            break;
    }
}

static void lever_controller_task() {
    static LeverState prev_fsm_state = LeverState::IDLE;

    while (true) {
        const bool requested = robot::controller.get_digital(robot::Controls::lever) || req_async;

        // Reset timers if the state has changed
        if (state != prev_fsm_state) {
            lever.timers_reset();
            prev_fsm_state = state;
        }

        apply_lever_state(state);

        // Skip exit_condition while IDLE
        if (state != LeverState::IDLE) {
            last_exit = lever.exit_condition();
        }

        switch (state) {
            case LeverState::IDLE:
                if (requested) {
                    state = LeverState::SCORE;
                }
                break;

            case LeverState::SCORE:
                if (!requested) {
                    state = LeverState::RETRACT;
                } 
                
                // We allow the PID to exit in autonomous
                else if (pros::competition::is_autonomous() &&
                           last_exit != ez::RUNNING) {
                    state = LeverState::RETRACT;
                }
                break;

            case LeverState::RETRACT:
                req_async = false;
                if (requested) {
                    state = LeverState::SCORE;
                } else if (last_exit != ez::RUNNING){
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

LeverState get_state() {
    return state;
}

ez::exit_output get_pid_exit() {
    if (state == LeverState::IDLE) {
        return ez::RUNNING;
    }
    return last_exit;
}

void score_async() {
    req_async = true;
    state = LeverState::SCORE;
}

void retract_async() {
    req_async = false;
    state = LeverState::RETRACT;
}

bool score(std::uint32_t timeout_ms) {
    score_async();
    const std::uint32_t start = pros::millis();
    
    while (pros::millis() - start < timeout_ms) {
        if (get_state() != LeverState::SCORE) {
            return true;
        }
        pros::delay(core::util::DELAY_TIME);
    }

    retract_async(); // Jammed, reset
    return false;
}

void initialize() {
    lever.exit_condition_set(
        LEVER_EXIT_SMALL_MS, LEVER_EXIT_SMALL_DEG, LEVER_EXIT_BIG_MS, 
        LEVER_EXIT_BIG_DEG, LEVER_EXIT_VEL_MS, LEVER_EXIT_MA_MS);
    lever_task = std::make_unique<pros::Task>(lever_controller_task);
}

}  // namespace lever

#endif
