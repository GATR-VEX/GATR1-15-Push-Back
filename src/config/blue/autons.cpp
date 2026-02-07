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
    subsystems::pistons::safe_extend(subsystems::matchloader);
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

    subsystems::color_sort::wait_until_balls_scored(LONG_GRACE_TIMEOUT_MS, SHORT_GRACE_TIMEOUT_MS);
    subsystems::intake::stop();
}

}  // namespace blue

#endif
