#include "core/subsystems/drive.hpp"
#include "core/globals.hpp"

#include "pros/llemu.hpp"

namespace page_selector {

void print_telemetry_data() {
    const auto pose = globals::drive_chassis.getPose();
    pros::lcd::print(2, "X: %f", pose.x);
    pros::lcd::print(3, "Y: %f", pose.y);
    pros::lcd::print(4, "Theta: %f", pose.theta);
    lemlib::telemetrySink()->info("Chassis pose: {}", pose);    
}

// Add util pages here

}  // namespace page_selector

