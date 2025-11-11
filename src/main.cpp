#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
// #include "pros/device.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include "main.h"

// Motor Groups
pros::MotorGroup right_motors({11,-12,13, 14},pros::MotorGearset::blue);
pros::MotorGroup left_motors({-17,18,-19,-20},pros::MotorGearset::blue);


// Drivetrain
lemlib::Drivetrain drivetrain(&left_motors,
							  &right_motors,
							  10.75,
							  lemlib::Omniwheel::NEW_325,
							  450,
							  3);

// Sensors
pros::Imu imu(1);
pros::Rotation vertical_rot(-10);
pros::Rotation horizontal_rot(-9);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_rot, lemlib::Omniwheel::NEW_275, 0.5);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_rot, lemlib::Omniwheel::NEW_275, -3.5);
lemlib::OdomSensors odom_sensors(&vertical_tracking_wheel,
								 nullptr,
								 &horizontal_tracking_wheel,
								 nullptr,
								 &imu);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(8, // proportional gain (kP)
                                              20, // integral gain (kI)
                                              28, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              30, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              100, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
											  
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// Chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        odom_sensors,
						&throttleCurve,
						&steerCurve
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
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
	 // set position to x:0, y:0, heading:0
    //chassis.setPose(0, 0, 0);
    chassis.moveToPose(15,35,90,4000, {.horizontalDrift=2, .lead=.3, .earlyExitRange=4});
	chassis.moveToPose(-8,26,-90,4000, {.horizontalDrift=2, .lead=.1, .earlyExitRange=4});
	chassis.moveToPose(-10,47,0,4000, {.horizontalDrift=2, .lead=0});



	//chassis.moveToPoint(0,30,1000);

	//chassis.turnToHeading(90, 10000);
	// chassis.moveToPoint(0,0,1000);

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
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        chassis.arcade(leftY, rightX);
        // delay to save resources
        pros::delay(10);                              // Run for 20 ms then update
	}
}