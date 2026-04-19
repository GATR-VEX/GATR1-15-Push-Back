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

namespace {

std::unique_ptr<pros::Task> lever_task;

static ez::PID lever_up{0.9, 0.0, 0.16, 0.0, "LeverUp"};
static ez::PID lever_down{0.9, 0.0, 0.55, 0.0, "LeverDown"};

static bool last_held = false;
static volatile bool g_bottom_reset_requested = false;

// Homing: down-PID + EZ exit, then tare. Holding the lever cancels (no tare).
static void home_and_tare() {
    lever_down.variables_reset();
    lever_down.timers_reset();
    lever_down.target_set(HOMING_TARGET_DEG);

    const std::uint32_t t0 = pros::millis();
    while (true) {
        if (robot::controller.get_digital(robot::Controls::lever)) {
            globals::lever_motor.move(0);
            lever_down.variables_reset();
            lever_up.variables_reset();
            lever_up.target_set(SCORE_POSITION_DEG);
            return;
        }

        const double pos = globals::lever_motor.get_position();
        globals::lever_motor.move(lever_down.compute(pos));

        if (lever_down.exit_condition() != ez::RUNNING) {
            break;
        }
        if (pros::millis() - t0 >= 3000) {
            break;
        }
        pros::delay(core::util::DELAY_TIME);
    }

    globals::lever_motor.move(0);
    globals::lever_motor.tare_position();
    lever_down.variables_reset();
    lever_up.variables_reset();
    lever_up.target_set(HOME_POSITION_DEG);
}

static void lever_controller_task() {
    last_held = false;
    while (true) {
        const bool held = robot::controller.get_digital(robot::Controls::lever);

        // if (!held && (g_bottom_reset_requested || last_held)) {
        //     g_bottom_reset_requested = false;
        //     home_and_tare();
        // }

        if (held) {
            lever_up.target_set(SCORE_POSITION_DEG);
            pistons::safe_extend(pistons::gate);
        } else {
            lever_up.target_set(HOME_POSITION_DEG);
            pistons::safe_retract(pistons::gate);
        }

        const double pos = globals::lever_motor.get_position();
        globals::lever_motor.move(lever_up.compute(pos));

        last_held = held;
        pros::delay(core::util::DELAY_TIME);
    }
}

}  // namespace

LeverState get_state() {
    const double pos = globals::lever_motor.get_position();
    const bool held = robot::controller.get_digital(robot::Controls::lever);
    if (!held && std::fabs(pos - HOME_POSITION_DEG) < STOW_EPS_DEG) {
        return LeverState::IDLE;
    }
    return LeverState::ACTIVE;
}

void request_bottom_reset() {
    g_bottom_reset_requested = true;
}

void initialize() {
    lever_down.exit_condition_set(80, 8.0, 0, 0, 80, 200);
    lever_up.target_set(HOME_POSITION_DEG);
    home_and_tare();
    lever_task = std::make_unique<pros::Task>(lever_controller_task);
}

}  // namespace lever

#endif
