#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_ORANGE

namespace orange {

// Auburn Car Auto
void auton1() {
   
    // Open Hood
    subsystems::hood->retract();

    // Drive Forwards
    chassis.pid_drive_set(55_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with middle goal
    chassis.pid_turn_set(-35, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive Forwards into lower middle goal
    chassis.pid_drive_set(4_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score middle 
    subsystems::intake::reverse();
    pros::delay(1000);
    subsystems::intake::stop();

    // Align with middle goal
    chassis.pid_turn_set(-50, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive to matchloader
    chassis.pid_drive_set(-80_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-83_in);
    subsystems::matchloader->extend();
    chassis.pid_wait();

    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive into matchloader
    subsystems::intake::collect();
    chassis.pid_drive_set(17_in, 80, true);
    chassis.pid_wait();

    for(int i = 0; i < 4; i++){
        chassis.pid_drive_set(7_in, MAX_SPEED);
        chassis.pid_wait();
        chassis.pid_drive_set(-7_in, MAX_SPEED);
        chassis.pid_wait();
    }
    subsystems::intake::stop();

    // Drive to long goal
    chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-10_in);
    subsystems::matchloader->retract();
    chassis.pid_wait();

    // Score long
    subsystems::intake::score_long();
    pros::delay(3000);
    subsystems::intake::stop();
 

}

void skills(){

    subsystems::intake::reverse();

}

}  // namespace orange

#endif
