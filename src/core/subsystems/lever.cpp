#include "core/subsystems/lever.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <cmath>
#include <memory>

#include "pros/rtos.hpp"

#ifdef ROBOT_BLUE

namespace lever {

static std::unique_ptr<pros::Task> lever_task;
static LeverState current_state = LeverState::IDLE;
static bool zero_requested = false;

void request_zero() {
    zero_requested = true;
}

LeverState get_state() {
    return current_state;
}

static void apply_motor(LeverState state) {
    switch (state) {
        case LeverState::IDLE:
        case LeverState::ZERO:
            pistons::safe_retract(pistons::gate);
            globals::lever_motor.move(0);
            break;

        case LeverState::SCORE:
            pistons::safe_extend(pistons::gate);
            globals::lever_motor.move(SCORE_POWER);
            break;

        case LeverState::SCORE_SLOW:
            pistons::safe_extend(pistons::gate);
            globals::lever_motor.move(SCORE_SLOW_POWER);
            break;

        case LeverState::RETURN:
            pistons::safe_retract(pistons::gate);
            globals::lever_motor.move(RETURN_POWER);
            break;
    }
}

static void lever_controller_task() {
    while (true) {

        // bool held = false;
        // if (zero_requested && current_state != LeverState::ZERO) {
        //     current_state = LeverState::ZERO;
        // }

        // switch (current_state) {
        //     case LeverState::ZERO:
        //         globals::lever_motor.tare_position();
        //         zero_requested = false;
        //         state = LeverState::IDLE;
        //         break;

        //     case LeverState::IDLE:
        //         if (held) {
        //             state = LeverState::SCORE;
        //         }
        //         break;

        //     case LeverState::SCORE:
        //         if (!held) {
        //             state = LeverState::RETURN;
        //         } else if (USE_SCORE_SLOW_BY_POSITION &&
        //                    globals::lever_motor.get_position() >= SCORE_SLOW_AT_POSITION) {
        //             state = LeverState::SCORE_SLOW;
        //         }
        //         break;

        //     case LeverState::SCORE_SLOW:
        //         if (!held) {
        //             state = LeverState::RETURN;
        //         }
        //         break;

        //     case LeverState::RETURN:
        //         // Cancel return -> go back to scoring immediately if button is held again.
        //         if (held) {
        //             state = LeverState::SCORE;
        //         } else {
        //             // "Eventually" return to IDLE once we're back near the home position.
        //             if (std::fabs(globals::lever_motor.get_position()) <= RETURN_IDLE_POSITION_EPS) {
        //                 state = LeverState::IDLE;
        //             }
        //         }
        //         break;
        // }

        // apply_motor(state);
        pros::delay(core::util::DELAY_TIME);
    }
}

void initialize() {
    lever_task = std::make_unique<pros::Task>(lever_controller_task);
}

}  // namespace lever

#endif