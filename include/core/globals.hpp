#pragma once

#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

#include "EZ-Template/api.hpp"
#include "api.h"

extern ez::Drive chassis;

namespace globals {

// Sensors
extern pros::Imu imu;
extern pros::Optical optical_color_sort;

// Tracking wheels
extern ez::tracking_wheel vert_tracker;
extern ez::tracking_wheel horiz_tracker;

// Auton selector
extern pros::adi::DigitalIn selectButton;

// Intake (4 motors)
extern pros::MotorGroup intake_bottom_stage;
extern pros::Motor intake_top_stage;
extern pros::Motor intake_indexer;

// Pneumatics
extern pros::adi::Pneumatics piston_matchloader;
extern pros::adi::Pneumatics piston_indexer;
extern pros::adi::Pneumatics piston_wing;
#ifdef ROBOT_ORANGE
extern pros::adi::Pneumatics piston_hood;
#endif

}  // namespace globals
