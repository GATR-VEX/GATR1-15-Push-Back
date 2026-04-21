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

void apply_driver_input(IntakeState& final_state) {
    // Priority: score (long/middle) > collect > reverse > stop
    if (robot::controller.get_digital(robot::Controls::score_middle)) {
        final_state = IntakeState::SCORE_MIDDLE;
    } else if (robot::controller.get_digital(robot::Controls::score_long)) {
        final_state = IntakeState::SCORE_LONG;
    } else if (robot::controller.get_digital(robot::Controls::matchloader) || 
               robot::controller.get_digital(robot::Controls::intake)) {
        final_state = IntakeState::COLLECT;
    } else if (robot::controller.get_digital(robot::Controls::reverse)) {
        final_state = IntakeState::REVERSE;
    } else {
        final_state = IntakeState::STOP;
    }
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
            set_top_power(INTAKE_SPEED_SLOW);
            break;

        case IntakeState::SCORE_LONG:
            pistons::safe_extend(pistons::four_bar);
            pistons::safe_extend(pistons::gate);
            pistons::safe_extend(pistons::intake);
            set_bottom_power(INTAKE_SPEED);
            set_top_power(INTAKE_SPEED);
            break;

        case IntakeState::SCORE_MIDDLE:
            pistons::safe_retract(pistons::four_bar);
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

void score_long() { set_target_state(IntakeState::SCORE_LONG); }

void score_middle() { set_target_state(IntakeState::SCORE_MIDDLE); }

void reverse() { set_target_state(IntakeState::REVERSE); }

void reverse_slow() { set_target_state(IntakeState::REVERSE_SLOW); }

#endif

}  // namespace intake
