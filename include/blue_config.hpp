#pragma once

#include <cstdint>

#include "lemlib/api.hpp"
#include "pros/controller.hpp"
#include "pros/motors.hpp"

namespace robot {
inline constexpr const char* NAME = "blue";

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

namespace ports {
inline constexpr std::int8_t DRIVE_RIGHT_FRONT = 11;
inline constexpr std::int8_t DRIVE_RIGHT_REAR = 13;
inline constexpr std::int8_t DRIVE_RIGHT_MIDDLE = -12;
inline constexpr std::int8_t DRIVE_RIGHT_AUX = 14;

inline constexpr std::int8_t DRIVE_LEFT_FRONT = -17;
inline constexpr std::int8_t DRIVE_LEFT_MIDDLE = 18;
inline constexpr std::int8_t DRIVE_LEFT_REAR = -19;
inline constexpr std::int8_t DRIVE_LEFT_AUX = -20;
}  // namespace ports

namespace sensors {
inline constexpr std::int8_t IMU = 1;
inline constexpr std::int8_t VERTICAL_ROTATION = -10;
inline constexpr std::int8_t HORIZONTAL_ROTATION = -9;
}  // namespace sensors

namespace drive {
inline constexpr pros::motor_gearset_e_t GEARSET = pros::MotorGearset::blue;
inline constexpr float TRACK_WIDTH = 10.75F;
inline constexpr lemlib::Omniwheel::wheelDiameter WHEEL_MODEL = lemlib::Omniwheel::NEW_325;
inline constexpr float WHEEL_RPM = 450.0F;
inline constexpr float HORIZONTAL_DRIFT = 3.0F;
}  // namespace drive

namespace odom {
inline constexpr lemlib::Omniwheel::wheelDiameter HORIZONTAL_WHEEL = lemlib::Omniwheel::NEW_275;
inline constexpr lemlib::Omniwheel::wheelDiameter VERTICAL_WHEEL = lemlib::Omniwheel::NEW_275;
inline constexpr float HORIZONTAL_OFFSET = 0.5F;
inline constexpr float VERTICAL_OFFSET = -3.5F;
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

inline constexpr Gains LATERAL{8.0, 20.0, 28.0, 3.0, 1.0, 100, 3.0, 500, 0.0};
inline constexpr Gains ANGULAR{3.0, 0.0, 30.0, 3.0, 1.0, 100, 3.0, 100, 0.0};
}  // namespace pid

struct Controls {
    static constexpr pros::controller_digital_e_t intake = pros::E_CONTROLLER_DIGITAL_A;
    static constexpr pros::controller_digital_e_t outtake = pros::E_CONTROLLER_DIGITAL_B;
    static constexpr pros::controller_digital_e_t wings = pros::E_CONTROLLER_DIGITAL_X;
    static constexpr pros::controller_digital_e_t ejector = pros::E_CONTROLLER_DIGITAL_Y;

    static constexpr pros::controller_analog_e_t driveX = pros::E_CONTROLLER_ANALOG_LEFT_X;
    static constexpr pros::controller_analog_e_t driveY = pros::E_CONTROLLER_ANALOG_LEFT_Y;
    static constexpr pros::controller_analog_e_t turnX = pros::E_CONTROLLER_ANALOG_RIGHT_X;
};

}  // namespace robot

