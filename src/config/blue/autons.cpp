#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_BLUE

namespace blue {

void match_auton() {
    // --- Phase 1: Middle Goal Engagement ---
    // Drive backward toward the center of the field
    chassis.pid_drive_set(-34_in, 90, true);
    chassis.pid_wait();

    // Pivot to align the back of the robot with the middle goal
    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Controlled backup into the goal for scoring
    chassis.pid_drive_set(-9_in, SLOW_SPEED, true);
    chassis.pid_wait();

    // Score the middle goal and reset intake
    subsystems::intake::score_middle();
    pros::delay(1000);
    subsystems::intake::stop();

    // --- Phase 2: Matchloading ---
    // Long drive toward the matchloader; extend piston mid-drive to save time
    chassis.pid_drive_set(53_in, DRIVE_SPEED, true);
    chassis.pid_wait_until(40_in);
    subsystems::pistons::safe_extend(subsystems::matchloader);
    chassis.pid_wait();

    // Face the matchloader directly
    chassis.pid_turn_set(0_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Begin intake and move forward to collect rings
    subsystems::intake::collect();
    chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // "Jiggle" the drivetrain to ensure rings settle properly in the intake
    for (int i = 0; i < 2; i++) {
        chassis.pid_drive_set(2_in, DRIVE_SPEED, true);
        chassis.pid_wait();
        chassis.pid_drive_set(-2_in, DRIVE_SPEED, true);
        chassis.pid_wait();
    }
    chassis.pid_wait();

    // --- Phase 3: Transition & Color Sorting ---
    // Reposition and score while checking for the correct alliance color
    chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    subsystems::intake::score_long();    
    subsystems::color_sort::wait_for_color(subsystems::color_sort::Color::RED, 5000);
    subsystems::intake::stop();

    // Clear the scoring zone
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Reset matchloader for the next cycle
    subsystems::pistons::safe_retract(subsystems::matchloader);
    
    // --- Phase 4: Secondary Goal & Clearing ---
    chassis.pid_turn_set(45_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Pulse intake in reverse to clear any jams
    subsystems::intake::reverse();
    pros::delay(1000);

    subsystems::pistons::safe_extend(subsystems::matchloader);

    chassis.pid_turn_set(0_deg, TURN_SPEED, true);
    chassis.pid_wait();
    
    // Collect and drive to final scoring position
    subsystems::intake::collect();
    chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    pros::delay(2000);

    chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    // Final long score sequence
    subsystems::intake::score_long();   
    pros::delay(1000);
    subsystems::intake::stop(); 

    // --- Phase 5: Final Position / Descore ---
    chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(75_deg, TURN_SPEED, true);
    chassis.pid_wait();

    // Use a swing turn to tuck the robot's corner into position
    chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 20);
    chassis.pid_wait();

    chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
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

}  // namespace blue

#endif
