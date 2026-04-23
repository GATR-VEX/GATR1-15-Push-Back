#include "core/subsystems/intake.hpp"
#include "core/subsystems/lever.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"

#include "pros/rtos.hpp"

namespace intake {

#ifdef ROBOT_BLUE

void check_lever_override(IntakeState& final_state) {
    if (lever::get_state() != lever::LeverState::IDLE) {
        final_state = IntakeState::STOP;
    }
}

void set_intake_power(int power) {
    globals::intake_bottom_stage.move(power);
}

void apply_driver_input(IntakeState& final_state) {
    if (robot::controller.get_digital(robot::Controls::intake) ||
        robot::controller.get_digital(robot::Controls::matchloader)) {
        final_state = IntakeState::FAST;
    } else if (robot::controller.get_digital(robot::Controls::reverse)) {
        final_state = IntakeState::REVERSE;
    } else {
        final_state = IntakeState::STOP;
    }
}

void apply_state(IntakeState state) {
    switch (state) {
        case IntakeState::STOP:
            pistons::safe_extend(pistons::intake);
            set_intake_power(0);
            break;

        case IntakeState::FAST:
            pistons::safe_extend(pistons::intake);
            set_intake_power(INTAKE_SPEED);
            break;

        case IntakeState::SLOW:
            pistons::safe_extend(pistons::intake);
            set_intake_power(INTAKE_SPEED_SLOW);
            break;

        case IntakeState::REVERSE:
            pistons::safe_retract(pistons::intake);
            set_intake_power(-INTAKE_SPEED);
            break;

        case IntakeState::REVERSE_SLOW:
            pistons::safe_retract(pistons::intake);
            set_intake_power(-INTAKE_SPEED_SLOW);
            break;
    }

}

void stop() { set_target_state(IntakeState::STOP); }

void fast() { set_target_state(IntakeState::FAST); }

void slow() { set_target_state(IntakeState::SLOW); }

void reverse() { set_target_state(IntakeState::REVERSE); }

void reverse_slow() { set_target_state(IntakeState::REVERSE_SLOW); }

#endif

}  // namespace intake
