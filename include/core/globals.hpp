#pragma once

#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"

#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

#include "EZ-Template/api.hpp"
#include "api.h"

namespace globals {

// Drive
extern pros::MotorGroup right_motors;
extern pros::MotorGroup left_motors;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis drive_chassis;
extern ez::Drive chassis;

// Sensors
extern pros::Imu imu;
extern pros::Rotation vertical_rot;
extern pros::Rotation horizontal_rot;
extern pros::Optical optical_color_sort;

// Odometry
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::OdomSensors odom_sensors;

// Controllers
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;

// Intake (4 motors)
extern pros::MotorGroup intake_bottom_stage;
extern pros::Motor intake_top_stage;
extern pros::Motor intake_indexer;

// Pneumatics
extern pros::adi::Pneumatics piston_matchloader;
extern pros::adi::Pneumatics piston_indexer;
extern pros::adi::Pneumatics piston_wing;
extern pros::adi::Pneumatics piston_hood;

}  // namespace globals
