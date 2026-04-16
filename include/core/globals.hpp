#pragma once

#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

#include "EZ-Template/api.hpp"
#include "api.h"

extern ez::Drive chassis;

namespace globals {

// Sensors
extern pros::Imu imu;
extern pros::Optical optical_color_sort;

// Auton selector
extern pros::adi::DigitalIn selectButton;

// Intake motors
extern pros::MotorGroup intake_bottom_stage;
#ifdef ROBOT_ORANGE
extern pros::Motor intake_top_stage;
#endif

// Pneumatics
extern pros::adi::Pneumatics piston_matchloader;
extern pros::adi::Pneumatics piston_intake;
extern pros::adi::Pneumatics piston_wing;
extern pros::adi::Pneumatics piston_gate;
extern pros::adi::Pneumatics piston_four_bar;

#ifdef ROBOT_BLUE
// Blue-only lever (two motors; use negative port in ports.hpp to reverse one side)
extern pros::MotorGroup lever_motor;
#endif

}  // namespace globals
