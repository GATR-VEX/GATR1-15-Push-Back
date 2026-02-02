#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_BLUE

namespace blue {

// Auburn Car Auto
void auton1() {

    // Open Hood
    subsystems::hood->extend();

    // Drive Backwards
    chassis.pid_drive_set(-32_in, 90, true);
    chassis.pid_wait();

    // Align with middle goal
    chassis.pid_turn_set(45, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive Backwards into middle goal
    chassis.pid_drive_set(-7_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score middle 
    subsystems::intake::score_slow();
    pros::delay(1000);
    subsystems::intake::stop();

    // Drive to matchloader
    chassis.pid_drive_set(51_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(40_in);
    subsystems::matchloader->extend();
    chassis.pid_wait();

    chassis.pid_turn_set(0_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // // Drive into matchloader
    // subsystems::intake::collect();
    // chassis.pid_drive_set(15_in, SLOW_SPEED, true);
    // chassis.pid_wait();

    // for(int i = 0; i < 3; i++){
    //     chassis.pid_drive_set(3_in, MAX_SPEED);
    //     chassis.pid_wait();
    //     chassis.pid_drive_set(-3_in, MAX_SPEED);
    //     chassis.pid_wait();
    // }
    // subsystems::intake::stop();

    // // Drive to long goal
    // chassis.pid_drive_set(-27_in, DRIVE_SPEED, true);
    // chassis.pid_wait_until(-10_in);
    // subsystems::matchloader->retract();
    // chassis.pid_wait();

    // // Score long
    // subsystems::intake::score_long();
    // subsystems::color_sort::wait_for_color(subsystems::color_sort::Color::BLUE, 3000);
    // subsystems::intake::stop();

    // // Drive to long goal
    // chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

    // // Align with middle goal
    // chassis.pid_turn_set(45, TURN_SPEED, true);
    // chassis.pid_wait();

    // // Drive to long goal
    // chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

    // // Align with middle goal
    // chassis.pid_turn_set(0, TURN_SPEED, true);
    // chassis.pid_wait();

    // subsystems::wing->retract();

    // // Score balls with wing
    // chassis.pid_drive_set(-22_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

}

// PID tuning: drive 24 in fwd/back, turn 90° + 90° + 180°
void auton2() {
    // Drive forward 24 in
    chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Drive backward 24 in
    chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Turn 90 degrees
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Turn 90 degrees again
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Turn 180 degrees
    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();
}

void auton3() {
    subsystems::intake::score_slow();
}

}  // namespace blue

#endif
