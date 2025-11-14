#include "core/subsystems/drive.hpp"
#include "core/globals.hpp"

#include <memory>

#include "lemlib/logger/telemetrySink.hpp"
#include "pros/lcd.hpp"
#include "pros/rtos.hpp"

namespace subsystems::drive {

std::unique_ptr<pros::Task> telemetry_task;

void run_telemetry() {
    while (true) {
        const auto pose = globals::drive_chassis.getPose();
        pros::lcd::print(0, "X: %f", pose.x);
        pros::lcd::print(1, "Y: %f", pose.y);
        pros::lcd::print(2, "Theta: %f", pose.theta);
        lemlib::telemetrySink()->info("Chassis pose: {}", pose);
        pros::delay(50);
    }
}

void initialize() {
    globals::right_motors.set_gearing(robot::drive::GEARSET);
    globals::left_motors.set_gearing(robot::drive::GEARSET);
    globals::drive_chassis.calibrate();

    telemetry_task = std::make_unique<pros::Task>(run_telemetry);
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

