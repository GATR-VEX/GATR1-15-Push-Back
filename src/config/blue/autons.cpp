#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_BLUE

namespace blue {

void match_auton_blue() { match_auton(subsystems::color_sort::Color::RED); }
void match_auton_red() { match_auton(subsystems::color_sort::Color::BLUE); }

void elims_auton_blue() { elims_auton(subsystems::color_sort::Color::RED); }
void elims_auton_red() { elims_auton(subsystems::color_sort::Color::BLUE); }

void match_auton(subsystems::color_sort::Color color) {
    // --- Phase 1: Middle Goal Scoring ---
    // Drive backward toward the center of the field
    chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Pivot to align the back of the robot with the middle goal
    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Backup slowly into the goal for scoring
    chassis.pid_drive_set(-9_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Score the middle goal
    subsystems::intake::score_middle();
    pros::delay(1000);
    subsystems::intake::stop();

    // --- Phase 2: Matchloading ---
    // Drive toward the matchloader; extend piston mid-drive
    chassis.pid_drive_set(53_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(40_in);
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_wait();

    // Face the matchloader directly
    chassis.pid_turn_set(0_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Begin intake and move forward to collect balls slower
    subsystems::intake::collect();
    chassis.pid_drive_set(12_in, 65, true);
    chassis.pid_wait();

    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    for (int i = 0; i < 3; i++) {
        chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
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
    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Shoots out all balls in the corner
    subsystems::intake::reverse();
    pros::delay(1000);

    // Extend matchloader to get balls from matchloader then straightens itself
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_turn_set(0_deg, TURN_SPEED, true);
    chassis.pid_wait();
    
    // Collect and drive to final scoring position
    subsystems::intake::collect();
    chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    for (int i = 0; i < 3; i++) {
        chassis.pid_drive_set(3.5_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(-3.5_in, DRIVE_SPEED, true);
        chassis.pid_wait();
    }
    chassis.pid_wait();
    chassis.pid_drive_set(-30_in, 55, true);
    chassis.pid_wait();
    
    // Final long score sequence
    subsystems::intake::score_long();   
    pros::delay(500);
    subsystems::intake::score_slow();
    pros::delay(1500);
    subsystems::intake::stop(); 

    subsystems::pistons::safe_retract(subsystems::matchloader);

    // --- Phase 5: Final Position / Descore ---
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(75_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Use a swing turn to tuck the robot's corner into position
    chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 20);
    chassis.pid_wait();

    chassis.pid_drive_set(-20_in, 50, true);
    chassis.pid_wait();
}


void elims_auton(subsystems::color_sort::Color color) {
    // --- Phase 1: Middle Goal Scoring ---
    // Drive backward toward the center of the field
    chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Pivot to align the back of the robot with the middle goal
    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Backup slowly into the goal for scoring
    chassis.pid_drive_set(-9_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Score the middle goal
    subsystems::intake::score_middle();
    pros::delay(1000);
    subsystems::intake::stop();

    // --- Phase 2: Matchloading ---
    // Drive toward the matchloader; extend piston mid-drive
    chassis.pid_drive_set(53_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(40_in);
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_wait();

    // Face the matchloader directly
    chassis.pid_turn_set(0_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Begin intake and move forward to collect balls slower
    subsystems::intake::collect();
    chassis.pid_drive_set(12_in, 65, true);
    chassis.pid_wait();

    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // --- Phase 3: Scoring Long Goal ---
    // Move to long goal and score 
    chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    subsystems::intake::score_long();    

    // detect color of ball and wait until red is detected and stop
    subsystems::color_sort::wait_for_color(color, 2000);
    subsystems::intake::stop();

    // Micro reverse intake in reduce possibility for red leaving the top
    subsystems::intake::reverse();
    pros::delay(50);
    subsystems::intake::stop();

    subsystems::pistons::safe_retract(subsystems::matchloader);

    // --- Phase 5: Final Position / Descore ---
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(75_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Use a swing turn to tuck the robot's corner into position
    chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 20);
    chassis.pid_wait();

    chassis.pid_drive_set(-20_in, 50, true);
    chassis.pid_wait();

    // Reverse to spit out the blue balls in the intake
    subsystems::intake::reverse();
    pros::delay(2000);
    subsystems::intake::stop();
}


void skills_auton() {
    // Drive Backwards
    chassis.pid_drive_set(-47_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Turn to face matchloader 
    chassis.pid_turn_set(-90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive into matchloader 1
    subsystems::pistons::safe_extend(subsystems::matchloader);
    subsystems::intake::collect();
    chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    subsystems::color_sort::wait_for_ball(MATCHLOAD_TIMEOUT_MS);
    subsystems::intake::stop();

    // Back out & drive around matchloader
    chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    subsystems::pistons::safe_retract(subsystems::matchloader);

    chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45); // params: direction, angle, speed, still side speed
    chassis.pid_wait();

    chassis.pid_turn_set(-90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-70_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // swing to align with long goal
    chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45); // params: direction, angle, speed, still side speed
    chassis.pid_wait();

    // drive into long goal
    chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    subsystems::intake::score_long();
    pros::delay(5000);
    subsystems::intake::stop();
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

}  // namespace blue

#endif
