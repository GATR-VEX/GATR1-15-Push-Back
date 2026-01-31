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
    subsystems::hood->extend();

    // Drive Forwards
    chassis.pid_drive_set(32_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with middle goal
    chassis.pid_turn_set(-45, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive Forwards into lower middle goal
    chassis.pid_drive_set(7_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score middle 
    subsystems::intake::reverse();
    pros::delay(1000);
    subsystems::intake::stop();
    // Drive to matchloader
    chassis.pid_drive_set(-51_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-40_in);
    subsystems::matchloader->extend();
    chassis.pid_wait();

    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive into matchloader
    subsystems::intake::collect();
    chassis.pid_drive_set(15_in, SLOW_SPEED, true);
    chassis.pid_wait();

    for(int i = 0; i < 3; i++){
        chassis.pid_drive_set(3_in, MAX_SPEED);
        chassis.pid_wait();
        chassis.pid_drive_set(-3_in, MAX_SPEED);
        chassis.pid_wait();
    }
    subsystems::intake::stop();

    // Drive to long goal
    chassis.pid_drive_set(-27_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-10_in);
    subsystems::matchloader->retract();
    chassis.pid_wait();

    // Score long
    subsystems::intake::score_long();
    pros::delay(3000);
    subsystems::intake::stop();


}

}  // namespace orange

#endif
