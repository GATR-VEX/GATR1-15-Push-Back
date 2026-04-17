#include "screen/pages.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"
#include "core/subsystems/pistons.hpp"
#include "core/subsystems/comp_timer.hpp"
#include "core/subsystems/lever.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"
#include "core/config.hpp"
#include "screen/screen_idle.hpp"

#include "main.h"
#include "pros/rtos.hpp"

void initialize() {
    // Wait for ADI ports to be initialized
    pros::delay(500);

    // Initialize Subsystems
    pistons::initialize();
    drive::initialize();
    intake::initialize();
#ifdef ROBOT_BLUE
    lever::initialize();
#endif

    // Initialize EZ-Template auton selector
    add_autons();
    ez::as::initialize();
    screen_idle::init();

    // Initialize debug screen task (displays color sort etc. on blank pages)
    utils_pages::initialize();

    // Update optical sensor every 15ms instead of every 100ms
    globals::optical_color_sort.set_integration_time(15);
    globals::optical_color_sort.set_led_pwm(75);

    // Rumble controller to indicate IMU calibration status
    robot::controller.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    screen_idle::show_idle();
    screen_idle::resume();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() { screen_idle::pause(); }

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
    // Reset PID targets and sensors
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();                  
    chassis.odom_xyt_set(0_in, 0_in, 0_deg); 
    chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
    
    // Ensure global intake state is stopped before auton starts
    intake::stop();
    
    // Run the selected autonomous routine
    ez::as::auton_selector.selected_auton_call();
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
    // Set drive brake mode to coast for opcontrol
    chassis.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);

    // Set desired default piston states
    pistons::safe_retract(pistons::matchloader); // Close matchloader

    // Initialize competition timer
    comp_timer::initialize();

    while (true) {
        // Run the drive mode
        drive::chassis_controller(ez::SPLIT);

        // Update piston states based on controller input
        pistons::safe_update(pistons::matchloader);
        pistons::safe_update(pistons::wing);
        pistons::safe_update(pistons::four_bar); /// TODO: The four-bar needs to go up and stay up when wing used

        // Update competition timer (buzzes at 20s, 10-1s countdown)
        comp_timer::update();
        
        // Small delay to prevent task from consuming too much CPU
        pros::delay(core::util::DELAY_TIME);
    }
}
