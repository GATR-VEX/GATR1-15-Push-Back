#include "main.h"
#include "config/orange/autons.hpp"

#include <vector>

#include "core/config.hpp"
#include "core/globals.hpp"

#ifdef ROBOT_ORANGE

void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(17.4, 0.0, 170.00);        // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(8.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.5, 0.05, 25.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(250_ms, 2_deg, 500_ms, 4_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(150_ms, 2_deg, 300_ms, 4_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(200_ms, 1_in, 500_ms, 2_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void add_autons() {
    // Use limit switch to select autons
    ez::as::limit_switch_lcd_initialize(&globals::selectButton);

    // Autonomous Selector using LLEMU
    ez::as::auton_selector.autons_add({
        {"Match Auto Blue\nLow Goal Setup", orange::match_auton_blue},
        {"Match Auto Red\nLow Goal Setup", orange::match_auton_red},
        {"Elims Blue\nLow Goal Setup", orange::elims_auton_blue},
        {"Elims Red\nnLow Goal Setup", orange::elims_auton_red},
        {"Skills Auto", orange::skills_auton},
        {"PID Tuning", orange::pid_tuning_auton},
    });
}

#endif
