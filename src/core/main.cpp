#include "core/selector.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/util.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void initialize() {

    // Wait for ADI ports to be initialized
    pros::delay(500);

    // Initialize selector and register autons and util pages
    page_selector::initialize();

    // Initialize drive subsystem (chassis, motors, sensors)
    subsystems::drive::initialize();

    // Initialize intake subsystem (starts intake controller task)
    subsystems::intake::initialize();

    // Initialize piston subsystem
    subsystems::initialize_pistons();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    // Ensure global intake state is stopped before auton starts
    subsystems::intake::stop();
    
    // Run the selected autonomous routine
    page_selector::selector.selected_auton_call();

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    while (true) {
        // Update arcade drive based on controller input
        subsystems::drive::update_arcade();

        // Update piston states based on controller input
        subsystems::matchloader->update();
        subsystems::wing->update();
        subsystems::hood->update();
        
        // Small delay to prevent task from consuming too much CPU
        pros::delay(core::util::DELAY_TIME);
    }
}
