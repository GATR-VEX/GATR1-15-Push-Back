/**
 * @file autons.cpp
 * @brief Orange robot autonomous routines.
 */

#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_ORANGE

namespace orange {

void match_auton_blue() { match_auton(color_sort::Color::RED); }
void match_auton_red() { match_auton(color_sort::Color::BLUE); }

void elims_auton_blue() { elims_auton(color_sort::Color::RED); }
void elims_auton_red() { elims_auton(color_sort::Color::BLUE); }

void match_auton(color_sort::Color color) {
    // --- Phase 1: Matchloading first set of balls ---
    chassis.pid_drive_set(30.5_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(15_in);
    pistons::safe_extend(pistons::matchloader);
    chassis.pid_wait();

    chassis.pid_turn_set(-90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    intake::collect();
    chassis.pid_drive_set(8.5_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    pros::delay(1750);

    // --- Phase 2: score in long goal ---
    chassis.drive_angle_set(-88_deg);
    chassis.pid_drive_set(-29_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-1_in);
    intake::reverse(); // unjam macro
    pros::delay(150);
    intake::stop(); // end unjam macro
    chassis.pid_wait_until(-20_in);
    chassis.drive_angle_set(-90_deg);
    chassis.pid_wait_until(-24_in);
    intake::score_long();
    chassis.pid_wait();

    // Score in long goal, stop on opposite color
    // If color not found AND ball in intake, try again
    if(!color_sort::wait_for_color(color, 2000) && 
       color_sort::is_ball_in_intake()){
        intake::stop();
        pros::delay(100);
        intake::score_long();
        color_sort::wait_for_color(color, 2000); // try again if jammed
    }
    pros::delay(200); // delay time for last ball to score
    intake::stop();

    // --- Phase 3: Matchloader refill #1 ---
    chassis.pid_drive_set(10_in, SLOW_SPEED, true);
    chassis.pid_wait();
    intake::score_long(); // ditch the 3 opposite color balls at the top of the intake

    chassis.pid_drive_set(19_in, SLOW_SPEED, true);
    chassis.pid_wait();
    intake::collect();
    pros::delay(2100);
    intake::stop();

    // --- Phase 4: Score middle goal ---
    chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 81, 15);
    chassis.pid_wait();

    chassis.pid_drive_set(-50_in, DRIVE_SPEED + 5, true);
    chassis.pid_wait();
    intake::score_middle();
    pros::delay(3000);
    intake::stop();

    // --- Phase 5: Back to matchloader refill #2 ---
    chassis.pid_drive_set(52_in, DRIVE_SPEED + 5, true);
    chassis.pid_wait();
    chassis.pid_turn_set(-90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    intake::collect();
    chassis.pid_drive_set(8.5_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    pros::delay(2100);
    intake::stop();

    // --- Phase 6: Score bottom goal---
    chassis.pid_swing_set(ez::RIGHT_SWING, -22_deg, 80, 15);
    chassis.pid_wait_quick_chain();
    pistons::safe_retract(pistons::matchloader);

    chassis.pid_drive_set(-68_in, DRIVE_SPEED + 5, true);
    chassis.pid_wait();

    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(7_in, SLOW_SPEED, true);
    chassis.pid_wait_until(5_in);
    intake::reverse();
    chassis.pid_wait();
}

void elims_auton(color_sort::Color color) {}

void skills_auton() {
    intake::collect();
}


void pid_tuning_auton() {
    // Drive forward 48 in
    chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Drive backward 24 in
    chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Drive backward 24 in
    chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    // Turn 90 degrees
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Turn 180 degrees
    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Turn 180 degrees
    chassis.pid_turn_set(0_deg, TURN_SPEED, ez::ccw);
    chassis.pid_wait();
    
    // Print Yaw to brain
    while(true) {
        pros::lcd::print(3, "Yaw: %f", globals::imu.get_yaw());
        pros::delay(100);
    }
}

}  // namespace orange

#endif
