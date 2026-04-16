#ifdef ROBOT_BLUE

#include "core/subsystems/lever.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <cmath>
#include <memory>

#include "pros/rtos.hpp"

namespace lever {

// Tune these once the lever mechanics are known.
inline constexpr int SCORE_POWER = 127;
inline constexpr int SCORE_SLOW_POWER = 80;
inline constexpr int RETURN_POWER = -127;

// When returning, consider "home" reached when we're close to 0.
inline constexpr double RETURN_IDLE_POSITION_EPS = 5.0;

// If you want SCORE->SCORE_SLOW based on position, enable and tune.
inline constexpr bool USE_SCORE_SLOW_BY_POSITION = false;
inline constexpr double SCORE_SLOW_AT_POSITION = 0.0;

static std::unique_ptr<pros::Task> lever_task;
static State state = State::IDLE;
static bool zero_requested = false;

static bool lever_button_held() {
    return robot::controller.get_digital(robot::Controls::lever);
}

void request_zero() {
    zero_requested = true;
}

State get_state() {
    return state;
}

static void apply_motor(State s) {
    switch (s) {
        case State::IDLE:
        case State::ZERO:
            globals::lever_motor.move(0);
            break;

        case State::SCORE:
            globals::lever_motor.move(SCORE_POWER);
            break;

        case State::SCORE_SLOW:
            globals::lever_motor.move(SCORE_SLOW_POWER);
            break;

        case State::RETURN:
            globals::lever_motor.move(RETURN_POWER);
            break;
    }
}

static void lever_task_fn() {
    while (true) {
        // Only react to driver input in opcontrol.
        bool held = lever_button_held();
        if (pros::competition::is_autonomous() || pros::competition::is_disabled()) {
            held = false;
        }

        // Allow cancel/override:
        // If a zero is requested, do it ASAP and return to IDLE.
        if (zero_requested && state != State::ZERO) {
            state = State::ZERO;
        }

        switch (state) {
            case State::IDLE:
                if (held) {
                    state = State::SCORE;
                }
                break;

            case State::SCORE:
                if (!held) {
                    state = State::RETURN;
                } else if (USE_SCORE_SLOW_BY_POSITION &&
                           globals::lever_motor.get_position() >= SCORE_SLOW_AT_POSITION) {
                    state = State::SCORE_SLOW;
                }
                break;

            case State::SCORE_SLOW:
                if (!held) {
                    state = State::RETURN;
                }
                break;

            case State::RETURN:
                // Cancel return -> go back to scoring immediately if button is held again.
                if (held) {
                    state = State::SCORE;
                } else {
                    // "Eventually" return to IDLE once we're back near the home position.
                    if (std::fabs(globals::lever_motor.get_position()) <= RETURN_IDLE_POSITION_EPS) {
                        state = State::IDLE;
                    }
                }
                break;

            case State::ZERO:
                // Zero out sensors/encoder by taring the motor position.
                // If later you use a limit switch, replace this with the proper routine.
                globals::lever_motor.tare_position();
                zero_requested = false;
                state = State::IDLE;
                break;
        }

        apply_motor(state);
        pros::delay(core::util::DELAY_TIME);
    }
}

void initialize() {
    // Start the task once. The state machine handles driver inputs internally.
    lever_task = std::make_unique<pros::Task>(lever_task_fn);
}

}  // namespace lever

#endif