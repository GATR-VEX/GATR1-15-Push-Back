#include "core/subsystems/drive.hpp"

#include <memory>

#include "core/config.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/imu.hpp"
#include "pros/lcd.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"

namespace subsystems::drive {
namespace {

pros::MotorGroup make_right_motors() {
    return pros::MotorGroup({robot::ports::DRIVE_RIGHT_FRONT,
                             robot::ports::DRIVE_RIGHT_MIDDLE,
                             robot::ports::DRIVE_RIGHT_REAR,
                             robot::ports::DRIVE_RIGHT_AUX});
}

pros::MotorGroup make_left_motors() {
    return pros::MotorGroup({robot::ports::DRIVE_LEFT_FRONT,
                             robot::ports::DRIVE_LEFT_MIDDLE,
                             robot::ports::DRIVE_LEFT_REAR,
                             robot::ports::DRIVE_LEFT_AUX});
}

pros::MotorGroup right_motors = make_right_motors();
pros::MotorGroup left_motors = make_left_motors();

lemlib::Drivetrain drivetrain(&left_motors,
                              &right_motors,
                              robot::drive::TRACK_WIDTH,
                              robot::drive::WHEEL_MODEL,
                              robot::drive::WHEEL_RPM,
                              robot::drive::HORIZONTAL_DRIFT);

pros::Imu imu(robot::sensors::IMU);
pros::Rotation vertical_rot(robot::sensors::VERTICAL_ROTATION);
pros::Rotation horizontal_rot(robot::sensors::HORIZONTAL_ROTATION);

lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_rot,
                                                robot::odom::HORIZONTAL_WHEEL,
                                                robot::odom::HORIZONTAL_OFFSET);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_rot,
                                              robot::odom::VERTICAL_WHEEL,
                                              robot::odom::VERTICAL_OFFSET);

lemlib::OdomSensors odom_sensors(&vertical_tracking_wheel,
                                 nullptr,
                                 &horizontal_tracking_wheel,
                                 nullptr,
                                 &imu);

const auto& lateral = robot::pid::LATERAL;
const auto& angular = robot::pid::ANGULAR;

lemlib::ControllerSettings lateral_controller(
    static_cast<float>(lateral.kP),
    static_cast<float>(lateral.kI),
    static_cast<float>(lateral.kD),
    static_cast<float>(lateral.anti_windup),
    static_cast<float>(lateral.small_error_range),
    static_cast<float>(lateral.small_error_timeout_ms),
    static_cast<float>(lateral.large_error_range),
    static_cast<float>(lateral.large_error_timeout_ms),
    static_cast<float>(lateral.max_acceleration));

lemlib::ControllerSettings angular_controller(
    static_cast<float>(angular.kP),
    static_cast<float>(angular.kI),
    static_cast<float>(angular.kD),
    static_cast<float>(angular.anti_windup),
    static_cast<float>(angular.small_error_range),
    static_cast<float>(angular.small_error_timeout_ms),
    static_cast<float>(angular.large_error_range),
    static_cast<float>(angular.large_error_timeout_ms),
    static_cast<float>(angular.max_acceleration));

lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve steer_curve(3, 10, 1.019);

lemlib::Chassis drive_chassis(drivetrain,
                              lateral_controller,
                              angular_controller,
                              odom_sensors,
                              &throttle_curve,
                              &steer_curve);

std::unique_ptr<pros::Task> telemetry_task;

void run_telemetry() {
    while (true) {
        const auto pose = drive_chassis.getPose();
        pros::lcd::print(0, "X: %f", pose.x);
        pros::lcd::print(1, "Y: %f", pose.y);
        pros::lcd::print(2, "Theta: %f", pose.theta);
        lemlib::telemetrySink()->info("Chassis pose: {}", pose);
        pros::delay(50);
    }
}

}  // namespace

void initialize() {
    right_motors.set_gearing(robot::drive::GEARSET);
    left_motors.set_gearing(robot::drive::GEARSET);
    drive_chassis.calibrate();

    telemetry_task = std::make_unique<pros::Task>(run_telemetry);
}

void update_arcade() {
    const auto forward = robot::controller.get_analog(robot::Controls::driveY);
    const auto turn = robot::controller.get_analog(robot::Controls::turnX);
    drive_chassis.arcade(forward, turn);
}

lemlib::Chassis& chassis() {
    return drive_chassis;
}

}  // namespace subsystems::drive

