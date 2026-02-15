#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_ORANGE

namespace orange {

void match_auton_blue() { match_auton(subsystems::color_sort::Color::RED); }
void match_auton_red() { match_auton(subsystems::color_sort::Color::BLUE); }

void elims_auton_blue() { elims_auton(subsystems::color_sort::Color::RED); }
void elims_auton_red() { elims_auton(subsystems::color_sort::Color::BLUE); }

void match_auton(subsystems::color_sort::Color color) {

    // Open Hood
    subsystems::pistons::safe_extend(subsystems::hood);

    subsystems::intake::collect();
    pros::delay(200);
    subsystems::intake::stop();

    // --- Phase 1: Middle Goal Scoring ---
    chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with middle goal
    chassis.pid_turn_set(-45, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive Forwards into lower middle goal
    chassis.pid_drive_set(4_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score middle
    subsystems::intake::reverse();
    pros::delay(1000);
    subsystems::intake::stop();

    // Drive to matchloader
    chassis.pid_drive_set(-46_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-40_in);
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_wait();

    chassis.pid_turn_set(182_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // -- Phase 2: Matchloading --
    subsystems::intake::collect();
    chassis.pid_drive_set(14.5_in, 55, true);
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

    // --- Phase 3: Scoring Long Goal ---
    // Move to long goal and score 
    chassis.pid_drive_set(-30_in, 55, true);
    chassis.pid_wait();
    
    subsystems::intake::score_long();    

    // detect color of ball and wait until red is detected and stop
    subsystems::color_sort::wait_for_color(color, 3000);
    subsystems::intake::stop();

    // Micro reverse intake in reduce possiblity for red leaving the top
    subsystems::intake::reverse();
    pros::delay(50);
    subsystems::intake::stop();

    // Drives forward to move closer to coner to extake
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Retract matchloader
    subsystems::pistons::safe_retract(subsystems::matchloader);
    
    // --- Phase 4: Secondary Goal & Clearing ---
    chassis.pid_turn_set(130_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Shoots out all balls in the corner
    subsystems::intake::reverse();
    pros::delay(1000);

    // Extend matchloader to get balls from matchloader then straightens itself
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_turn_set(182_deg, TURN_SPEED, true);
    chassis.pid_wait();
    
    // Collect and drive to final scoring position
    subsystems::intake::collect();
    chassis.pid_drive_set(11_in, 65, true);
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
    subsystems::intake::score_long();   
    pros::delay(1500);
    subsystems::intake::reverse();
    pros::delay(300);
    subsystems::intake::score_long();   
    pros::delay(500);
    subsystems::intake::stop(); 

    subsystems::pistons::safe_retract(subsystems::matchloader);

    // --- Phase 5: Final Position / Descore ---
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(255_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // // Use a swing turn to tuck the robot's corner into position
    chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, SWING_SPEED, 20);
    chassis.pid_wait();

    chassis.pid_drive_set(-20_in, 50, true);
    chassis.pid_wait();
}


void elims_auton(subsystems::color_sort::Color color) {

    subsystems::pistons::safe_extend(subsystems::hood);

    subsystems::intake::collect();
    pros::delay(200);
    subsystems::intake::stop();

    // --- Phase 1: Middle Goal Scoring ---
    chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with middle goal
    chassis.pid_turn_set(-45, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive Forwards into lower middle goal
    chassis.pid_drive_set(4_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score middle
    subsystems::intake::reverse();
    pros::delay(1000);
    subsystems::intake::stop();

    // Drive to matchloader
    chassis.pid_drive_set(-46_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-40_in);
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_wait();

    chassis.pid_turn_set(182_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // -- Phase 2: Matchloading --
    subsystems::intake::collect();
    chassis.pid_drive_set(14.5_in, 55, true);
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

    // --- Phase 3: Scoring Long Goal ---
    // Move to long goal and score 
    chassis.pid_drive_set(-30_in, 55, true);
    chassis.pid_wait();
    
    subsystems::intake::score_long();    

    // detect color of ball and wait until red is detected and stop
    subsystems::color_sort::wait_for_color(color, 3000);
    subsystems::intake::stop();

    // Micro reverse intake in reduce possiblity for red leaving the top
    subsystems::intake::reverse();
    pros::delay(50);
    subsystems::intake::stop();

    // --- Phase 4: Final Position / Descore ---
    subsystems::pistons::safe_retract(subsystems::matchloader);
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(255_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // // Use a swing turn to tuck the robot's corner into position
    chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, SWING_SPEED, 20);
    chassis.pid_wait();

    subsystems::intake::reverse();
    chassis.pid_drive_set(-18_in, 50, true);
    chassis.pid_wait();
    pros::delay(2000);
    subsystems::intake::stop();

}


void skills_auton() {

    subsystems::pistons::safe_extend(subsystems::hood);

    subsystems::intake::collect();
    pros::delay(200);
    subsystems::intake::stop();

    // Drive Backwards
    chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Turn to face long goal 
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive into long goal and score
    chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    subsystems::intake::score_long();
    pros::delay(1000);
    subsystems::intake::stop();

    // Drive into matchloader 1
    chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(4_in);
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_wait();

    // Begin intake and move forward to collect balls slower
    subsystems::intake::collect();
    chassis.pid_drive_set(8_in, 55, true);
    chassis.pid_wait();

    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    for (int i = 0; i < 4; i++) {
        chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
    }
    chassis.pid_wait();

        // Back out & drive around matchloader
    chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Drive down side lane
    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-67_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-50_in);
    subsystems::pistons::safe_retract(subsystems::matchloader);
    chassis.pid_wait();

    // Drive in front of long goal
    subsystems::intake::stop();
    chassis.pid_turn_set(-180_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with long goal and score
    chassis.pid_turn_set(270_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-14_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    subsystems::intake::score_long();
    pros::delay(1500);
    subsystems::intake::stop();

    // Drive into matchloader 2
    chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(4_in);
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_wait();

    // Begin intake and move forward to collect balls slower
    subsystems::intake::collect();
    chassis.pid_drive_set(6_in, 65, true);
    chassis.pid_wait();

    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    for (int i = 0; i < 4; i++) {
        chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
    }
    chassis.pid_wait();

    // Drive into Long goal and score
    chassis.pid_drive_set(-27_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-8_in);
    chassis.pid_wait();
    subsystems::intake::score_long();
    pros::delay(1500);
    subsystems::intake::stop();
    subsystems::pistons::safe_retract(subsystems::matchloader);


    // get extra 2 balls and score them

    chassis.pid_drive_set(22, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();    
    subsystems::intake::collect();
    chassis.pid_drive_set(17, DRIVE_SPEED, true);
    chassis.pid_wait();    
    chassis.pid_drive_set(-17, DRIVE_SPEED, true);
    chassis.pid_wait();   
    chassis.pid_turn_set(270_deg, TURN_SPEED, true);
    chassis.pid_wait();   
    chassis.pid_drive_set(-23, DRIVE_SPEED, true);
    chassis.pid_wait();

    subsystems::intake::score_long();
    pros::delay(1500);
    subsystems::intake::stop();


    // Drive to park zone
    subsystems::pistons::safe_retract(subsystems::matchloader);

    chassis.pid_drive_set(7, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(11, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(70, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(40, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 10); // params: direction, angle, speed, still side speed
    chassis.pid_wait();

    chassis.pid_drive_set(8, DRIVE_SPEED, true);
    chassis.pid_wait();

    subsystems::pistons::safe_extend(subsystems::matchloader);

    pros::delay(500);

    chassis.pid_drive_set(40, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(-3, DRIVE_SPEED, true);
    subsystems::pistons::safe_retract(subsystems::matchloader);
    chassis.pid_wait();

    // chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45); // params: direction, angle, speed, still side speed
    // chassis.pid_wait();

    // chassis.pid_turn_set(-90_deg, TURN_SPEED, true);
    // chassis.pid_wait();
    // chassis.pid_drive_set(-70_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

    // // swing to align with long goal
    // chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45); // params: direction, angle, speed, still side speed
    // chassis.pid_wait();

    // // drive into long goal
    // chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
    // chassis.pid_wait();
    // subsystems::intake::score_long();
    // pros::delay(5000);
    // subsystems::intake::stop();
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
