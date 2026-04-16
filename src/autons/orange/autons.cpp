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
    
    intake::score();    

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
    intake::score();   
    pros::delay(700);
    intake::reverse();
    pros::delay(300);
    intake::score();   
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


void elims_auton(color_sort::Color color) {

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

    // Drive Forwards into lower middle goal
    chassis.pid_drive_set(4_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score middle
    intake::reverse();
    pros::delay(1000);
    intake::stop();

    // Drive to matchloader
    chassis.pid_drive_set(-46_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-40_in);
    pistons::safe_extend(pistons::matchloader);
    chassis.pid_wait();

    chassis.pid_turn_set(182_deg, TURN_SPEED, true);
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

    // --- Phase 3: Scoring Long Goal ---
    // Move to long goal and score 
    chassis.pid_drive_set(-30_in, 55, true);
    chassis.pid_wait();
    
    intake::score();    

    // detect color of ball and wait until red is detected and stop
    color_sort::wait_for_color(color, 3000);
    intake::stop();

    // Micro reverse intake in reduce possiblity for red leaving the top
    intake::reverse();
    pros::delay(50);
    intake::stop();

    // --- Phase 4: Final Position / Descore ---
    pistons::safe_retract(pistons::matchloader);
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(255_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // // Use a swing turn to tuck the robot's corner into position
    chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, SWING_SPEED, 20);
    chassis.pid_wait();

    intake::reverse();
    chassis.pid_drive_set(-18_in, 50, true);
    chassis.pid_wait();
    pros::delay(2000);
    intake::stop();

}


void skills_auton() {

    // Extend Hood
    pistons::safe_extend(pistons::four_bar);

    // Extend Wing, unnecessary but implemented just in case hardware is not properly setup
    intake::collect();
    pros::delay(200);
    intake::stop();

    // Drive Backwards
    chassis.pid_drive_set(-33_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Turn to face long goal 
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive into long goal and score
    chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    intake::score();
    pros::delay(1000);
    intake::stop();

    chassis.pid_drive_set(4_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Turn to face long goal 
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();

    pistons::safe_extend(pistons::matchloader);

    // Drive into matchloader 1
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Begin intake and move forward to collect balls slower
    intake::collect();
    chassis.pid_drive_set(10_in, 55, true);
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
    chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-67_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-50_in);
    pistons::safe_retract(pistons::matchloader);
    chassis.pid_wait();

    // Drive in front of long goal
    intake::stop();
    chassis.pid_turn_set(-180_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with long goal and score
    chassis.pid_turn_set(269_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    intake::score();
    pros::delay(1750);
    intake::stop();

    // Drive into matchloader 2
    chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(4_in);
    pistons::safe_extend(pistons::matchloader);
    chassis.pid_wait();

    // Begin intake and move forward to collect balls slower
    intake::collect();
    chassis.pid_drive_set(7_in, 65, true);
    chassis.pid_wait();

    // "Jiggle" the drivetrain to make sure all balls get out and into intake
    for (int i = 0; i < 5; i++) {
        chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
        chassis.pid_wait();
    }
    chassis.pid_wait();

    // Drive into Long goal and score
    chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(-8_in);
    chassis.pid_wait();
    intake::score();
    pros::delay(2250);
    intake::stop();
    pistons::safe_retract(pistons::matchloader);

    // get extra 2 balls and score them
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();    
    intake::collect();
    chassis.pid_drive_set(17_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    // Drive to long goal to score 2 additional balls
    chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
    chassis.pid_wait();   
    chassis.pid_turn_set(270_deg, TURN_SPEED, true);
    chassis.pid_wait();   
    chassis.pid_drive_set(-23, DRIVE_SPEED, true);
    chassis.pid_wait();
    intake::score();
    pros::delay(1500);
    intake::stop();

    // Drive down alley towards park zone
    pistons::safe_retract(pistons::matchloader);
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(11_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(70_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Approach park zone from alley
    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 10); // params: direction, angle, speed, still side speed
    chassis.pid_wait();

    // Drive close to park zone to slap matchloader ontop of park zone and not hit balls
    chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    pistons::safe_extend(pistons::matchloader);

    // Drive over park zone
    chassis.pid_drive_set(50_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Drive backwards slowly to be aligned with the park zone
    chassis.pid_drive_set(-10_in, 40, true);
    pistons::safe_retract(pistons::matchloader);
    chassis.pid_wait();

    // Drive forward for momentum
    chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Park
    chassis.pid_drive_set(-25.5_in, DRIVE_SPEED, true);
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
