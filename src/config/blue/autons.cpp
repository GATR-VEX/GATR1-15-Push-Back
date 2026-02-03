#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_BLUE

namespace blue {

void match_auton() {
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
}

void pid_tuning_auton() {
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

void skills_auton() {
    // TODO
}

}  // namespace blue

#endif
