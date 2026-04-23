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

    intake::collect();
    color_sort::wait_for_color(color_sort::Color::RED, 10000);
    intake::stop();

    while(true) {pros::delay(100);}


    // --- Phase 1: Matchloading first set of balls ---
    pistons::safe_extend(pistons::matchloader);

    chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();














    // Open Hood
    pistons::safe_extend(pistons::four_bar);

    intake::collect();
    pros::delay(200);
    intake::stop();

    // --- Phase 1: Middle Goal Scoring ---
    chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with middle goal
    chassis.pid_turn_set(-45, TURN_SPEED, true);
    chassis.pid_wait();

    intake::reverse();

    // Drive Forwards into lower middle goal
    chassis.pid_drive_set(4_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score middle
    intake::reverse();
    pros::delay(1500);
    intake::stop();

    // Drive to matchloader
    chassis.pid_drive_set(-48_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-40_in);
    pistons::safe_extend(pistons::matchloader);
    chassis.pid_wait();

    chassis.pid_turn_set(179_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // -- Phase 2: Matchloading --
    intake::collect();
    chassis.pid_drive_set(14.5_in, 35, true);
    chassis.pid_wait();

    pros::delay(500);

    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    for (int i = 0; i < 2; i++) {
        chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
    }
    chassis.pid_wait();

    chassis.pid_turn_set(182_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // --- Phase 3: Scoring Long Goal ---
    // Move to long goal and score 
    chassis.pid_drive_set(-30_in, 55, true);
    chassis.pid_wait();
    
    intake::score_long();    

    // detect color of ball and wait until red is detected and stop
    color_sort::wait_for_color(color, 1500);
    intake::stop();

    // Micro reverse intake in reduce possiblity for red leaving the top
    intake::reverse();
    pros::delay(50);
    intake::stop();

    // Drives forward to move closer to coner to extake
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Retract matchloader
    pistons::safe_retract(pistons::matchloader);
    
    // --- Phase 4: Secondary Goal & Clearing ---
    chassis.pid_turn_set(130_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Shoots out all balls in the corner
    intake::reverse();
    pros::delay(1000);

    // Extend matchloader to get balls from matchloader then straightens itself
    pistons::safe_extend(pistons::matchloader);
    chassis.pid_turn_set(182_deg, TURN_SPEED, true);
    chassis.pid_wait();
    
    // Collect and drive to final scoring position
    intake::collect();
    chassis.pid_drive_set(11_in, 45, true);
    chassis.pid_wait();

    pros::delay(500);
    
    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    for (int i = 0; i < 2; i++) {
        chassis.pid_drive_set(-3.5_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(3.5_in, DRIVE_SPEED, true);
        chassis.pid_wait();
    }
    chassis.pid_wait();
    chassis.pid_drive_set(-30_in, 55, true);
    chassis.pid_wait();
    
    // Final long score sequence
    intake::score_long();   
    pros::delay(700);
    intake::reverse();
    pros::delay(300);
    intake::score_long();   
    pros::delay(600);
    intake::stop(); 

    pistons::safe_retract(pistons::matchloader);

    // --- Phase 5: Final Position / Descore ---
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(255_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // // Use a swing turn to tuck the robot's corner into position
    chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, SWING_SPEED, 20);
    chassis.pid_wait_quick();

    chassis.pid_drive_set(-20_in, 50, true);
    chassis.pid_wait();
}


void elims_auton(color_sort::Color color) {}

void skills_auton() {}


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
