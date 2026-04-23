#include "main.h"
#include "EZ-Template/api.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

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

// Limit switch for auton selector
pros::adi::DigitalIn select_button(robot::ports::LIMIT_SWITCH_SELECT);

// Intake motors
pros::MotorGroup intake_bottom_stage({robot::ports::INTAKE_BOTTOM_STAGE_1,
                                      robot::ports::INTAKE_BOTTOM_STAGE_2});
#ifdef ROBOT_ORANGE
pros::Motor intake_top_stage(robot::ports::INTAKE_TOP_STAGE);
#endif

#ifdef ROBOT_BLUE
pros::MotorGroup lever_motor({robot::ports::LEVER_LEFT, 
                              robot::ports::LEVER_RIGHT});
#endif

// Optical sensor
pros::Optical optical_color_sort(robot::ports::OPTICAL_COLOR_SORT);

// Pneumatics
pros::adi::Pneumatics piston_matchloader(robot::ports::PISTON_MATCHLOADER_PORT, false);
pros::adi::Pneumatics piston_intake(robot::ports::PISTON_INTAKE_PORT, false);
pros::adi::Pneumatics piston_wing(robot::ports::PISTON_WING_PORT, false);
pros::adi::Pneumatics piston_gate(robot::ports::PISTON_GATE_PORT, false);
pros::adi::Pneumatics piston_four_bar(robot::ports::PISTON_FOUR_BAR_PORT, false);

}  // namespace globals
