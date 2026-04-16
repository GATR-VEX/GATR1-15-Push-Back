#include "core/subsystems/intake.hpp"
#include "core/subsystems/lever.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"

#include "pros/rtos.hpp"

#include <cstdint>
#include <optional>

namespace intake {

#ifdef ROBOT_BLUE

namespace {

// After reverse ends, wait this long with no reverse before restoring four-bar snapshot.
constexpr std::uint32_t kFourBarRestoreDelayMs = 1000;
std::optional<bool> four_bar_snapshot;
std::uint32_t last_time_reverse_seen_ms = 0;

void update_four_bar_reverse(IntakeState state) {
    const std::uint32_t now = pros::millis();

    // If reversing, extend four-bar, save initial state
    if (state == IntakeState::REVERSE || state == IntakeState::REVERSE_SLOW) {
        if (!four_bar_snapshot.has_value()) { 
            four_bar_snapshot = pistons::four_bar->is_extended();
        }
        pistons::safe_extend(pistons::four_bar);
        last_time_reverse_seen_ms = now;
        return;
    }

    // Nominal exit case: no snapshot, no reversing
    if (!four_bar_snapshot.has_value()) {
        return;
    }

    // Timer incomplete: busy-wait
    if (now - last_time_reverse_seen_ms < kFourBarRestoreDelayMs) {
        return;
    }

    // Restore four-bar to initial state
    if (four_bar_snapshot.value()) {
        pistons::safe_extend(pistons::four_bar);
    } else {
        pistons::safe_retract(pistons::four_bar);
    }
    four_bar_snapshot.reset();
}

}  // anonymous namespace

void check_lever_override(IntakeState& final_state) {
    if (lever::get_state() != lever::LeverState::IDLE) {
        final_state = IntakeState::STOP;
    }
}

void set_intake_power(int power) {
    globals::intake_bottom_stage.move(power);
}

IntakeState get_driver_state() {
    if (robot::controller.get_digital(robot::Controls::intake)) {
        return IntakeState::FAST;
    }
    if (robot::controller.get_digital(robot::Controls::reverse)) {
        return IntakeState::REVERSE;
    }
    return IntakeState::STOP;
}

void apply_state(IntakeState state) {
    switch (state) {
        case IntakeState::STOP:
            set_intake_power(0);
            break;

        case IntakeState::FAST:
            set_intake_power(INTAKE_SPEED);
            break;

        case IntakeState::SLOW:
            set_intake_power(INTAKE_SPEED_SLOW);
            break;

        case IntakeState::REVERSE:
            set_intake_power(-INTAKE_SPEED);
            break;

        case IntakeState::REVERSE_SLOW:
            set_intake_power(-INTAKE_SPEED_SLOW);
            break;
    }
    
    // Handle four-bar macro-action
    update_four_bar_reverse(state);
}

void stop() { set_target_state(IntakeState::STOP); }

void fast() { set_target_state(IntakeState::FAST); }

void slow() { set_target_state(IntakeState::SLOW); }

void reverse() { set_target_state(IntakeState::REVERSE); }

void reverse_slow() { set_target_state(IntakeState::REVERSE_SLOW); }

#endif

}  // namespace intake
