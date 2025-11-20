#include "core/subsystems/intake.hpp"
#include "core/subsystems/color_sort.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <memory>

#include "pros/motors.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

namespace subsystems::intake {

std::unique_ptr<pros::Task> intake_task;

// Target state that can be set from driver control or autonomous code
static IntakeState target_state = IntakeState::STOP;

 IntakeState get_driver_state() {
    if (robot::controller.get_digitial(robot::Controls::intake)){
        return IntakeState::COLLECT;
    } 
    else if (robot::controller.getditial(robot::Controls::score_long_goal)){
        return IntakeState::SCORE_LONG;
    }
    else if (robot::controller.getditial(robot::Controls::score_middle_goal)){
        return IntakeState::SCORE_MIDDLE;
    }
    else if (robot::controller.getditial(robot::Controls::reverse)){
        return IntakeState::REVERSE;
    }
    else{
        return IntakeState::STOP;
    }
}

void intake_controller_task() {
    while (true) {
        IntakeState final_state = target_state;

        if(!pros::competition::is_autonomous() && !pros::competition::is_disabled()){
            final_state = get_driver_state();
        }
        
        // COLOR SORT LOGIC
        // // Example code:
        // if (color_sort::is_wrong_color_detected() && intake::is_running()){
        //     final_state = IntakeState::EJECT;
        // }  

        apply_state(final_state);

        // Small delay to prevent the task from consuming too much CPU
        pros::delay(core::util::DELAY_TIME);
    }
}

void initialize() {
    intake_task = std::make_unique<pros::Task>(intake_controller_task);
}

void set_bottom_power(int power) {
    globals::intake_stage_motors.move(power);
}

void set_indexer_power(int power) {
    globals::intake_indexer_motor.move(power);
}


bool is_running() {
    // Check if intake motors are actually moving
    // This is useful mostly for color sort logic
    // - you need to know if the intake IS LITERALLY moving and SHOULD be moving to eject a ball
    //
    // Steps to implement:
    // 1. Get the actual velocity of the bottom intake motors:
    //    - Use: globals::intake_stage_motors.get_actual_velocity()
    // 2. Compare to the threshold:
    //    - If velocity is greater than INTAKE_VELOCITY_THRESHOLD, motors are running
    // 3. Return true if motors are running, false otherwise


    return false;
}

void apply_state(IntakeState state) {    
    switch (state) {
        case IntakeState::STOP:
            set_bottom_power(0);
            set_indexer_power(0);
            break;

        case IntakeState::SCORE_LONG:
            set_bottom_power(INTAKE_SPEED);
            set_indexer_power(INTAKE_SPEED);
            break;

        case IntakeState::SCORE_MIDDLE:
            set_bottom_power(INTAKE_SPEED);
            set_indexer_power(-INTAKE_SPEED);
            break;

        case IntakeState::COLLECT:
            set_bottom_power(INTAKE_SPEED);
            set_indexer_power(INTAKE_SPEED);
            break;

        case IntakeState::REVERSE:
            break;

        case IntakeState::EJECT:
            set_bottom_power(OUTTAKE_SPEED);
            set_indexer_power(-OUTTAKE_SPEED);
            //robot::subsystems::pistons::color_sort.extend();
            // pros::delay(core::color_sort::DELAY_TIME);
            //robot::subsystems::pistons::color_sort.retract();
            break;
    }
}

// Convenience functions for autonomous
void stop() { target_state = IntakeState::STOP; }

void collect() { target_state = IntakeState::COLLECT; }

void score_long() { target_state = IntakeState::SCORE_LONG; }

void score_middle() { target_state = IntakeState::SCORE_MIDDLE; }

void reverse() { target_state = IntakeState::REVERSE; }

}  // namespace subsystems::intake
