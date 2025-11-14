#include "core/subsystems/intake.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <cmath>
#include <memory>

#include "pros/motors.hpp"
#include "pros/rtos.hpp"

namespace subsystems::intake {

std::unique_ptr<pros::Task> intake_task;

void intake_controller_task() {
    while (true) {
        // TODO: Intake control logic:
        // 1. Read controller buttons:
        //    - robot::Controls::intake -> set intake on (forward)
        //    - robot::Controls::outtake -> set intake reverse
        //    - Otherwise -> intake off
        //
        // 2. Color sensing & sorting:
        //    - Read globals::optical_color_sort.get_hue()
        //    - Determine current alliance color (BLUE/RED) - can be detected from robot::NAME or set manually
        //    - If intake is running AND wrong color detected:
        //      * Reverse intake briefly to eject wrong color
        //      * Then resume normal intake
        //
        // 3. Set base motor outputs (can be overridden by color sort):
        //    - If intake button pressed: set_stage_power(127), set_indexer_power(127), set_rollers_power(127)
        //    - If outtake button pressed: set_stage_power(-127), set_indexer_power(-127), set_rollers_power(-127)
        //    - If color sort detects wrong color: temporarily override to reverse, then resume
        //    - Otherwise: set all to 0

        pros::delay(core::util::DELAY_TIME);
    }
}

void initialize() {
    intake_task = std::make_unique<pros::Task>(intake_controller_task);
}

void set_stage_power(int power) {
    globals::intake_stage_motors.move(power);
}

void set_indexer_power(int power) {
    globals::intake_indexer_motor.move(power);
}

void set_rollers_power(int power) {
    globals::intake_rollers_motor.move(power);
}

bool is_running() {
    // TODO: Check if intake motors are actually moving
    // Compare globals::intake_stage_motors.get_actual_velocity() to INTAKE_VELOCITY_THRESHOLD
    return false;
}

bool is_color_blue(double hue) {
    // TODO: Check if hue is in blue range (COLOR_BLUE_HUE_MIN to COLOR_BLUE_HUE_MAX)
    return false;
}

bool is_color_red(double hue) {
    // TODO: Check if hue is in red range (COLOR_RED_HUE_MIN to COLOR_RED_HUE_MAX, or wraps around)
    return false;
}

bool is_wrong_color_detected() {
    // TODO: Read globals::optical_color_sort.get_hue()
    // Determine alliance with some define for alliance color
    // Return true if detected color is opposite of alliance
    return false;
}

}  // namespace subsystems::intake
