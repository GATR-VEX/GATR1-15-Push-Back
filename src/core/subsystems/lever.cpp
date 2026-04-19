#include "core/subsystems/lever.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include "EZ-Template/api.hpp"

#include <cmath>
#include <memory>

#include "pros/rtos.hpp"

#ifdef ROBOT_BLUE

namespace lever {

static LeverState state = LeverState::IDLE;
static ez::exit_output g_last_pid_exit = ez::RUNNING;

static ez::PID lever_up{0.9, 0.0, 0.16, 0.0, "LeverUp"};
static ez::PID lever_down{0.9, 0.0, 0.55, 0.0, "LeverDown"};

namespace {

std::unique_ptr<pros::Task> lever_task;

void apply_lever_state(LeverState s) {
    const double pos = globals::lever_motor.get_position();

    switch (s) {
        case LeverState::IDLE:
            globals::lever_motor.move(0);
            pistons::safe_retract(pistons::gate);
            break;

        case LeverState::SCORE:
            lever_up.target_set(SCORE_POSITION_DEG);
            pistons::safe_extend(pistons::gate);
            globals::lever_motor.move(lever_up.compute(pos));
            break;

        case LeverState::RETRACT:
            lever_down.target_set(HOMING_TARGET_DEG);
            pistons::safe_retract(pistons::gate);
            globals::lever_motor.move(lever_down.compute(pos));
            break;

        case LeverState::ZERO:
            break;
    }
}

static bool retract_complete() {
    return g_last_pid_exit != ez::RUNNING && g_last_pid_exit != ez::ERROR_NO_CONSTANTS;
}

static void lever_controller_task() {
    while (true) {
        const bool held = robot::controller.get_digital(robot::Controls::lever);

        apply_lever_state(state);

        switch (state) {
            case LeverState::SCORE:
                g_last_pid_exit = lever_up.exit_condition();
                break;
            case LeverState::RETRACT:
            case LeverState::ZERO:
                g_last_pid_exit = lever_down.exit_condition();
                break;
            case LeverState::IDLE:
                g_last_pid_exit = ez::RUNNING;
                break;
        }

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

int last_pid_exit_raw() {
    return static_cast<int>(g_last_pid_exit);
}

void request_bottom_reset() {}

void initialize() {
    lever_up.exit_condition_set(500, 8.0, 0, 0, 80, 800);
    lever_down.exit_condition_set(500, 8.0, 0, 0, 80, 800);
    lever_task = std::make_unique<pros::Task>(lever_controller_task);
}

}  // namespace lever

#endif
