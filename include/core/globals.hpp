#pragma once

#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

namespace globals {

// Drive
extern pros::MotorGroup right_motors;
extern pros::MotorGroup left_motors;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis drive_chassis;

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

// Intake
extern pros::MotorGroup intake_stage_motors;
extern pros::Motor intake_indexer_motor;
extern pros::Motor intake_rollers_motor;

// Pneumatics
extern pros::adi::Pneumatics piston_matchloader;
extern pros::adi::Pneumatics piston_indexer;
extern pros::adi::Pneumatics piston_wings;

}  // namespace globals

