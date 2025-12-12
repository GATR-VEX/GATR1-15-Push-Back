#pragma once

#include "config/blue/ports.hpp"

#include "lemlib/api.hpp"
#include "pros/motors.hpp"

namespace robot {
inline constexpr const char* NAME = "blue";

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

namespace sensors {
inline constexpr std::int8_t IMU = ports::IMU;
inline constexpr std::int8_t VERTICAL_ROTATION = ports::VERTICAL_ROTATION;
inline constexpr std::int8_t HORIZONTAL_ROTATION = ports::HORIZONTAL_ROTATION;
}  // namespace sensors

namespace drive {
inline constexpr pros::v5::MotorGears GEARSET = pros::MotorGearset::blue;
inline constexpr float TRACK_WIDTH = 10.5F;
inline constexpr float WHEEL_MODEL = lemlib::Omniwheel::NEW_325;
inline constexpr float WHEEL_RPM = 450.0F;
inline constexpr float HORIZONTAL_DRIFT = 3.0F;

// Drive curve parameters (deadband, minOutput, curve)
inline constexpr float THROTTLE_DEADBAND = 3.0F;
inline constexpr float THROTTLE_MIN_OUTPUT = 10.0F;
inline constexpr float THROTTLE_CURVE = 1.019F;
inline constexpr float STEER_DEADBAND = 3.0F;
inline constexpr float STEER_MIN_OUTPUT = 10.0F;
inline constexpr float STEER_CURVE = 1.019F;
}  // namespace drive

namespace odom {
inline constexpr float HORIZONTAL_WHEEL = 1.85F;
inline constexpr float VERTICAL_WHEEL = 1.85F;
inline constexpr float HORIZONTAL_OFFSET = 0.0F;
inline constexpr float VERTICAL_OFFSET = 0.0F;
}  // namespace odom

namespace pid {
struct Gains {
    double kP;
    double kI;
    double kD;
    double anti_windup;
    double small_error_range;
    std::int32_t small_error_timeout_ms;
    double large_error_range;
    std::int32_t large_error_timeout_ms;
    double max_acceleration;
};

inline constexpr Gains LATERAL{18.0, 0, 80.0, 3, 1, 100, 3, 500, 20};
inline constexpr Gains ANGULAR{4.8, 0.0, 38.0, 3, 1, 100, 2, 400, 0};
}  // namespace pid

struct Controls {
    static constexpr pros::controller_digital_e_t intake = pros::E_CONTROLLER_DIGITAL_L1;
    static constexpr pros::controller_digital_e_t reverse = pros::E_CONTROLLER_DIGITAL_L2;
    static constexpr pros::controller_digital_e_t score_long_goal = pros::E_CONTROLLER_DIGITAL_R1;
    static constexpr pros::controller_digital_e_t score_middle_goal = pros::E_CONTROLLER_DIGITAL_R2;

    static constexpr pros::controller_digital_e_t wings = pros::E_CONTROLLER_DIGITAL_DOWN;
    static constexpr pros::controller_digital_e_t ejector = pros::E_CONTROLLER_DIGITAL_B;

    static constexpr pros::controller_analog_e_t driveX = pros::E_CONTROLLER_ANALOG_LEFT_X;
    static constexpr pros::controller_analog_e_t driveY = pros::E_CONTROLLER_ANALOG_LEFT_Y;
    static constexpr pros::controller_analog_e_t turnX = pros::E_CONTROLLER_ANALOG_RIGHT_X;
};

}  // namespace robot

