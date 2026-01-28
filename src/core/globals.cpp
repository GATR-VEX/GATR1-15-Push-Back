#include "main.h"
#include "EZ-Template/api.hpp"

#include "core/globals.hpp"
#include "core/config.hpp"

#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

// EZ-Template Drive Constructor (global namespace)
ez::Drive chassis(
    {robot::ports::DRIVE_LEFT_FRONT,
    robot::ports::DRIVE_LEFT_MIDDLE,
    robot::ports::DRIVE_LEFT_REAR,
    robot::ports::DRIVE_LEFT_AUX}, 
    {robot::ports::DRIVE_RIGHT_FRONT,
    robot::ports::DRIVE_RIGHT_MIDDLE,
    robot::ports::DRIVE_RIGHT_REAR,
    robot::ports::DRIVE_RIGHT_AUX},
    robot::sensors::IMU,
    robot::drive::WHEEL_MODEL,
    robot::drive::WHEEL_RPM);

namespace globals {

// Sensors
pros::Imu imu(robot::sensors::IMU);

// Tracking wheels for odometry
// EZ-Template tracking_wheel constructor takes: (port, wheel_diameter, distance_to_center, ratio)
ez::tracking_wheel vert_tracker(robot::sensors::VERTICAL_ROTATION,
                                robot::odom::VERTICAL_WHEEL,
                                robot::odom::VERTICAL_OFFSET);
ez::tracking_wheel horiz_tracker(robot::sensors::HORIZONTAL_ROTATION,
                                 robot::odom::HORIZONTAL_WHEEL,
                                 robot::odom::HORIZONTAL_OFFSET);

// Limit switch for auton selector
pros::adi::DigitalIn selectButton(robot::ports::LIMIT_SWITCH_SELECT);

// Intake motors (4 total)
pros::MotorGroup intake_bottom_stage({robot::ports::INTAKE_BOTTOM_STAGE_1,
                                      robot::ports::INTAKE_BOTTOM_STAGE_2});
pros::Motor intake_top_stage(robot::ports::INTAKE_TOP_STAGE);
pros::Motor intake_indexer(robot::ports::INTAKE_INDEXER);

// Optical sensor
pros::Optical optical_color_sort(robot::ports::OPTICAL_COLOR_SORT);

// Pneumatics
pros::adi::Pneumatics piston_matchloader(robot::ports::PISTON_MATCHLOADER, false);
pros::adi::Pneumatics piston_indexer(robot::ports::PISTON_INDEXER, false);
pros::adi::Pneumatics piston_wing(robot::ports::PISTON_WING, false);
pros::adi::Pneumatics piston_hood(robot::ports::PISTON_HOOD, false);

}  // namespace globals
