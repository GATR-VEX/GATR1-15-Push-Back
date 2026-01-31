#pragma once

#include "config/blue/ports.hpp"

#include "pros/motors.hpp"

inline constexpr int DRIVE_SPEED = 100;
inline constexpr int MAX_SPEED   = 127;
inline constexpr int SLOW_SPEED  = 60;
inline constexpr int TURN_SPEED  = 90;
inline constexpr int SWING_SPEED = 100;

namespace robot {
inline constexpr const char* NAME = "blue";

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

namespace sensors {
inline constexpr std::int8_t IMU                 = ports::IMU;
inline constexpr std::int8_t VERTICAL_ROTATION   = ports::VERTICAL_ROTATION;
inline constexpr std::int8_t HORIZONTAL_ROTATION = ports::HORIZONTAL_ROTATION;
}  // namespace sensors

namespace drive {
inline constexpr pros::v5::MotorGears GEARSET = pros::MotorGearset::blue;
inline constexpr float TRACK_WIDTH            = 10.75F;
inline constexpr float WHEEL_MODEL            = 3.25F;
inline constexpr float WHEEL_RPM              = 450.0F;
inline constexpr float HORIZONTAL_DRIFT       = 3.0F;

// Drive curve parameters (deadband, minOutput, curve)
inline constexpr float THROTTLE_DEADBAND      = 3.0F;
inline constexpr float THROTTLE_MIN_OUTPUT    = 10.0F;
inline constexpr float THROTTLE_CURVE         = 1.019F;
inline constexpr float STEER_DEADBAND         = 3.0F;
inline constexpr float STEER_MIN_OUTPUT       = 10.0F;
inline constexpr float STEER_CURVE            = 1.019F;

// Opcontrol constants
inline constexpr bool CURVE_BUTTONS_TOGGLE    = false;     // Enables modifying the controller curve with buttons on the joysticks
inline constexpr double DRIVE_ACTIVEBRAKE     = 0.0;       // Sets the active brake kP. We recommend ~2.  0 will disable.
inline constexpr double CURVE_DEFAULT_LEFT    = 0.25;      // Default curve for left stick (or single stick). If using tank, only this is used.
inline constexpr double CURVE_DEFAULT_RIGHT   = 2.25;      // Default curve for right stick (arcade only)
}  // namespace drive

namespace odom {
inline constexpr float HORIZONTAL_WHEEL       = 2.75F;
inline constexpr float VERTICAL_WHEEL         = 2.75F;
inline constexpr float HORIZONTAL_OFFSET      = 0.5F;
inline constexpr float VERTICAL_OFFSET        = -3.5F;
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
    static constexpr pros::controller_digital_e_t intake            = pros::E_CONTROLLER_DIGITAL_L1;
    static constexpr pros::controller_digital_e_t reverse           = pros::E_CONTROLLER_DIGITAL_L2;
    static constexpr pros::controller_digital_e_t score_long_goal   = pros::E_CONTROLLER_DIGITAL_R1;
    static constexpr pros::controller_digital_e_t score_middle_goal = pros::E_CONTROLLER_DIGITAL_R2;

    static constexpr pros::controller_digital_e_t wing              = pros::E_CONTROLLER_DIGITAL_RIGHT;
    static constexpr pros::controller_digital_e_t hood              = (pros::controller_digital_e_t)(-1);
    static constexpr pros::controller_digital_e_t matchloader       = pros::E_CONTROLLER_DIGITAL_Y;
};

}  // namespace robot

