#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"

namespace intake {

#ifdef ROBOT_ORANGE
namespace {

void set_bottom_power(int power) {
    globals::intake_bottom_stage.move(power);
}

void set_top_power(int power) {
    globals::intake_top_stage.move(power);
}

}  // anonymous namespace

void check_matchloader_override(IntakeState& final_state) {
    if (pistons::matchloader->is_extended()) {
        final_state = IntakeState::COLLECT;
    }
}

IntakeState get_driver_state() {
    // Priority: score buttons > collect > reverse > stop
    if (robot::controller.get_digital(robot::Controls::score)) {
        return IntakeState::SCORE;
    }
    if (robot::controller.get_digital(robot::Controls::matchloader)) {
        return IntakeState::SCORE_SLOW;
    }
    if (robot::controller.get_digital(robot::Controls::intake)) {
        return IntakeState::COLLECT;
    }
    if (robot::controller.get_digital(robot::Controls::reverse)) {
        return IntakeState::REVERSE;
    }
    return IntakeState::STOP;
}

void apply_state(IntakeState state) {
    switch (state) {
        case IntakeState::STOP:
            pistons::safe_retract(pistons::gate);
            pistons::safe_extend(pistons::intake);
            set_bottom_power(0);
            set_top_power(0);
            break;

        case IntakeState::COLLECT:
            pistons::safe_retract(pistons::gate);
            pistons::safe_extend(pistons::intake);
            set_bottom_power(INTAKE_SPEED);
            set_top_power(0);
            break;

        case IntakeState::SCORE:
            pistons::safe_extend(pistons::gate);
            pistons::safe_extend(pistons::intake);
            set_bottom_power(INTAKE_SPEED);
            set_top_power(INTAKE_SPEED);
            break;

        case IntakeState::SCORE_SLOW:
            pistons::safe_extend(pistons::gate);
            pistons::safe_extend(pistons::intake);
            set_bottom_power(INTAKE_SPEED_SLOW);
            set_top_power(INTAKE_SPEED_SLOW);
            break;

        case IntakeState::REVERSE:
            pistons::safe_retract(pistons::gate);
            pistons::safe_retract(pistons::intake);
            set_bottom_power(-INTAKE_SPEED);
            set_top_power(-INTAKE_SPEED);
            break;

        case IntakeState::REVERSE_SLOW:
            pistons::safe_extend(pistons::gate);
            pistons::safe_retract(pistons::intake);
            set_bottom_power(-INTAKE_SPEED_SLOW);
            set_top_power(-INTAKE_SPEED_SLOW);
            break;
    }
}

void stop() { set_target_state(IntakeState::STOP); }

void collect() { set_target_state(IntakeState::COLLECT); }

void score() { set_target_state(IntakeState::SCORE); }

void score_slow() { set_target_state(IntakeState::SCORE_SLOW); }

void reverse() { set_target_state(IntakeState::REVERSE); }

void reverse_slow() { set_target_state(IntakeState::REVERSE_SLOW); }

#endif

}  // namespace intake
