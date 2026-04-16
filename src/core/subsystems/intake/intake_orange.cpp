#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/config.hpp"

namespace intake {

#ifdef ROBOT_ORANGE
IntakeState get_driver_state() {
    // Priority order: score buttons > intake > reverse > stop
    if (robot::controller.get_digital(robot::Controls::score_long_goal)) {
        return IntakeState::SCORE_LONG;
    } else if (robot::controller.get_digital(robot::Controls::score_middle_fast_goal)) {
        return IntakeState::SCORE_MIDDLE_FAST;
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
            pistons::safe_retract(pistons::intake);
            break;

        case IntakeState::SCORE_LONG:
            set_bottom_power(INTAKE_SPEED);
            set_top_power(INTAKE_SPEED);
            pistons::safe_retract(pistons::intake);
            break;

        case IntakeState::SCORE_SLOW:
            set_bottom_power(INTAKE_SPEED_SLOW);
            set_top_power(INTAKE_SPEED_SLOW);
            pistons::safe_retract(pistons::intake);
            break;

        case IntakeState::SCORE_MIDDLE:
            set_bottom_power(INTAKE_SPEED);
            set_top_power(INTAKE_SPEED);
            pistons::safe_extend(pistons::intake);
            break;

        case IntakeState::COLLECT:
            set_bottom_power(INTAKE_SPEED);
            set_top_power(0);
            pistons::safe_retract(pistons::intake);
            break;

        case IntakeState::REVERSE:
            set_bottom_power(-INTAKE_SPEED);
            set_top_power(-INTAKE_SPEED);
            pistons::safe_retract(pistons::intake);
            break;

        case IntakeState::REVERSE_SLOW:
            set_bottom_power(-INTAKE_SPEED_SLOW);
            set_top_power(-INTAKE_SPEED_SLOW);
            pistons::safe_retract(pistons::intake);
            break;
    }
}

void stop() { set_target_state(IntakeState::STOP); }

void collect() { set_target_state(IntakeState::COLLECT); }

void score_long() { set_target_state(IntakeState::SCORE_LONG); }

void score_slow() { set_target_state(IntakeState::SCORE_SLOW); }

void score_middle() { set_target_state(IntakeState::SCORE_MIDDLE); }

void reverse() { set_target_state(IntakeState::REVERSE); }

void reverse_slow() { set_target_state(IntakeState::REVERSE_SLOW); }

#endif

}  // namespace intake

