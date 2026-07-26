/**
 * @file globals.hpp
 * @brief Global hardware instances shared across subsystems.
 */

#pragma once

#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

#include "EZ-Template/api.hpp"
#include "api.h"

/** EZ-Template 8-motor drive with IMU odometry. */
extern ez::Drive chassis;

namespace globals {

// Sensors
extern pros::Imu imu;
extern pros::Optical optical_color_sort;

/** Limit switch on the brain LCD auton selector (EZ-Template). */
extern pros::adi::DigitalIn select_button;

// Intake motors
extern pros::MotorGroup intake_bottom_stage;
#ifdef ROBOT_ORANGE
extern pros::MotorGroup intake_top_stage;
#endif

// Pneumatics
extern pros::adi::Pneumatics piston_matchloader;
extern pros::adi::Pneumatics piston_intake;
extern pros::adi::Pneumatics piston_wing;
extern pros::adi::Pneumatics piston_gate;
extern pros::adi::Pneumatics piston_four_bar;

#ifdef ROBOT_BLUE
extern pros::MotorGroup lever_motor;
#endif

}  // namespace globals
