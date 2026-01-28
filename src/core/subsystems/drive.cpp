#include "core/subsystems/drive.hpp"
#include "core/globals.hpp"
#include "core/config.hpp"

#include <memory>

#include "EZ-Template/api.hpp"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"

namespace subsystems::drive {

void initialize() {
    ez::ez_template_print();
    pros::delay(500);

    // Set up tracking wheels for odometry
    chassis.odom_tracker_back_set(&globals::horiz_tracker);
    chassis.odom_tracker_left_set(&globals::vert_tracker);

    // Configure chassis controls
    chassis.opcontrol_curve_buttons_toggle(false);    // Enables modifying the controller curve with buttons on the joysticks
    chassis.opcontrol_drive_activebrake_set(0.0);     // Sets the active brake kP. We recommend ~2.  0 will disable.
    chassis.opcontrol_curve_default_set(0.25, 2.25);  // Defaults for curve. If using tank, only the first parameter is used.

    // Set the drive to constants from config_autons.cpp
    default_constants();

    // Initialize chassis
    chassis.initialize();
}

// Tank control
void chassis_controller() {
    chassis.opcontrol_tank();
}

// Arcade control - pass ez::SPLIT or ez::SINGLE, and optionally flipped=true
void chassis_controller(ez::e_type stick_type, bool flipped) {
    if (flipped) {
        chassis.opcontrol_arcade_flipped(stick_type);
    } else {
        chassis.opcontrol_arcade_standard(stick_type);
    }
}

}  // namespace subsystems::drive

