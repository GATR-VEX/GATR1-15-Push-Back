/**
 * @file config.hpp
 * @brief Orange robot: drive tuning, controller bindings, and feature flags.
 */

#pragma once

#include "config/orange/ports.hpp"

#include "pros/motors.hpp"

inline constexpr int DRIVE_SPEED = 90;
inline constexpr int MAX_SPEED   = 127;
inline constexpr int SLOW_SPEED  = 60;
inline constexpr int TURN_SPEED  = 85;
inline constexpr int SWING_SPEED = 80;

namespace robot {
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

namespace sensors {
inline constexpr std::int8_t IMU                 = ports::IMU;
}  // namespace sensors

namespace drive {
inline constexpr float WHEEL_MODEL            = 3.25F;
inline constexpr float WHEEL_RPM              = 450.0F;

inline constexpr bool CURVE_BUTTONS_TOGGLE    = false;
inline constexpr double DRIVE_ACTIVEBRAKE     = 0.0;
inline constexpr double CURVE_DEFAULT_LEFT    = 0.25;
inline constexpr double CURVE_DEFAULT_RIGHT   = 4.25;
}  // namespace drive

/** Master controller button assignments for Orange robot. */
struct Controls {
    static constexpr pros::controller_digital_e_t intake                 = pros::E_CONTROLLER_DIGITAL_L1;
    static constexpr pros::controller_digital_e_t reverse                = pros::E_CONTROLLER_DIGITAL_Y;
    static constexpr pros::controller_digital_e_t score_long             = pros::E_CONTROLLER_DIGITAL_R1;
    static constexpr pros::controller_digital_e_t score_middle           = pros::E_CONTROLLER_DIGITAL_R2;
    static constexpr pros::controller_digital_e_t matchloader            = pros::E_CONTROLLER_DIGITAL_RIGHT;
    static constexpr pros::controller_digital_e_t four_bar               = pros::E_CONTROLLER_DIGITAL_B;
    static constexpr pros::controller_digital_e_t wing                   = pros::E_CONTROLLER_DIGITAL_L2;
};

inline constexpr bool ENABLE_COMP_TIMER = true;

}  // namespace robot
