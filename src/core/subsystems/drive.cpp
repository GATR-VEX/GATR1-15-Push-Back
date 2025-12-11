#include "core/subsystems/drive.hpp"
#include "core/globals.hpp"
#include "core/config.hpp"

#include <memory>

#include "lemlib/logger/telemetrySink.hpp"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"

namespace subsystems::drive {

void initialize() {
    globals::right_motors.set_gearing(robot::drive::GEARSET);
    globals::left_motors.set_gearing(robot::drive::GEARSET);
    globals::drive_chassis.calibrate();
}

void update_arcade() {
    const auto forward = robot::controller.get_analog(robot::Controls::driveY);
    const auto turn = robot::controller.get_analog(robot::Controls::turnX);
    globals::drive_chassis.arcade(forward, turn);
}

lemlib::Chassis& chassis() {
    return globals::drive_chassis;
}

}  // namespace subsystems::drive

