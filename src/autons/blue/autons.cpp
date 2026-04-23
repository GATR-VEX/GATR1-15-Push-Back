#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/lever.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/color_sort.hpp"

#include "pros/llemu.hpp"

#include "core/globals.hpp"

#ifdef ROBOT_BLUE

namespace blue {

void match_auton_blue() { match_auton(color_sort::Color::RED); }
void match_auton_red() { match_auton(color_sort::Color::BLUE); }

void elims_auton_blue() { elims_auton(color_sort::Color::RED); }
void elims_auton_red() { elims_auton(color_sort::Color::BLUE); }

void match_auton(color_sort::Color color) {
   // --- Phase 1: Matchloading first set of balls ---
   pistons::safe_extend(pistons::matchloader);

   chassis.pid_drive_set(-32_in, DRIVE_SPEED, true);
   chassis.pid_wait();

   chassis.pid_turn_set(-90_deg, TURN_SPEED, true);
   chassis.pid_wait();

   intake::fast();
   pistons::safe_extend(pistons::four_bar);
   chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
   chassis.pid_wait();
   pros::delay(750);

   // Phase 2: score in long goal
   chassis.pid_drive_set(-29_in, DRIVE_SPEED, true);
   chassis.pid_wait();

   // Attempt to score with lever, retry if necessary
   for (int i = 0; i < 2; i++) {
    if (lever::score(2000)) {
        break;
    }
    pros::delay(500);
   }
   intake::stop();

   // --- Phase 3: Wing long goal ---
   // TODO

}


void elims_auton(color_sort::Color color) {

}


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

}  // namespace blue

#endif
