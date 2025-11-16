#include "core/subsystems/intake.hpp"
#include "core/subsystems/color_sort.hpp"
#include "core/config.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include <memory>

#include "pros/motors.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

namespace subsystems::intake {

std::unique_ptr<pros::Task> intake_task;

// Target state that can be set from driver control or autonomous code
static IntakeState target_state = IntakeState::STOP;

void intake_controller_task() {
    while (true) {
        // DRIVER CONTROL LOGIC (Setting ENUM)
        // Steps to implement:
        // 1. Check if we're in competition mode 
        // 2. Read the controller buttons:
        //    - robot::controller.get_digital(robot::Controls::intake)
        //
        // We need to add support for scoring regular long goals and middle goals
        //    - IntakeState::SCORE_LONG & IntakeState::SCORE_MIDDLE
        //
        // Example code structure:
        // if (driver control is enabled) {
        //     if (intake button is pressed) {
        //         collect state is set
        //     } else if (outtake button is pressed) {
        //         reverse state is set
        //     } else {
        //         stop state is set
        //     }
        // }
        

        // COLOR SORT LOGIC
        // This section checks if we need to override the driver's command
        // to eject a wrong-color ball
        //
        // Steps to implement:
        // 1. Start with the driver's desired state: final_state = driver_state
        // 2. Check if we're collecting AND a wrong color is detected:
        //    - Use: color_sort::is_wrong_color_detected()
        //    - This function returns true if the optical sensor sees a ball
        //      that doesn't match our alliance color
        // 3. If both conditions are true (collecting + wrong color):
        //    - Override final_state to IntakeState::EJECT
        //    - This will reverse the motors to eject the wrong color
        //
        // Example code:
        // if (collect state is set and wrong color is detected) {
        //     eject state is set
        // }
        //
        // Note: The EJECT state should be functionally the same as score middle
        

        // SET MOTOR POWER VALUES
        // This section applies the final_state enum to the actual motors
        // The apply_state() function handles converting the enum to motor powers
        // You don't need to modify this - just call it with final_state
        
        apply_state(final_state);

        // Small delay to prevent the task from consuming too much CPU
        pros::delay(core::util::DELAY_TIME);
    }
}

void initialize() {
    intake_task = std::make_unique<pros::Task>(intake_controller_task);
}

void set_bottom_power(int power) {
    // Set power for bottom intake motors (initial intake stage)
    globals::intake_stage_motors.move(power);
}

void set_indexer_power(int power) {
    // Set power for indexer motor (middle stage - moves balls between bottom and top)
    globals::intake_indexer_motor.move(power);
}

void set_top_power(int power) {
    // Set power for top intake motor (final stage - for long goal scoring)
    globals::intake_rollers_motor.move(power);
}

bool is_running() {
    // Check if intake motors are actually moving
    // This is useful mostly for color sort logic
    // - you need to know if the intake IS LITERALLY moving and SHOULD be moving to eject a ball
    //
    // Steps to implement:
    // 1. Get the actual velocity of the bottom intake motors:
    //    - Use: globals::intake_stage_motors.get_actual_velocity()
    // 2. Compare to the threshold:
    //    - If velocity is greater than INTAKE_VELOCITY_THRESHOLD, motors are running
    // 3. Return true if motors are running, false otherwise


    return false;
}

void apply_state(IntakeState state) {
    // This function converts an IntakeState enum into actual motor powers
    // Each case sets the power for:
    //   - Bottom stage motors (intake_stage_motors): First/bottom stage of intake
    //   - Indexer motor (intake_indexer_motor): Middle stage - moves balls between bottom and top
    //   - Top intake motor (intake_rollers_motor): Final/top stage - for long goal scoring
    //
    // Power values:
    //   - Positive values (INTAKE_SPEED): Motors spin forward (intake direction)
    //   - Negative values (OUTTAKE_SPEED): Motors spin backward (outtake direction)
    //   - Zero: Motors stop
    
    switch (state) {
        case IntakeState::STOP:
            // All motors stopped - robot is not intaking or outtaking
            set_bottom_power(0);
            set_indexer_power(0);
            set_top_power(0);
            break;

        case IntakeState::SCORE_LONG:
            // Score ball into the long goal
            // All motors run forward to push ball through the system and into long goal
            
            // Intake should probobally just dictate some global state for the indexer piston since it 
            // will be determistically determined by scoring or not

            break;

        case IntakeState::SCORE_MIDDLE:
            // Score ball into the middle goal
            // Bottom stage and indexer run forward, but top intake should NOT run
            // (top intake is only for long goal)
            break;

        case IntakeState::COLLECT:
            set_bottom_power(INTAKE_SPEED);
            set_indexer_power(INTAKE_SPEED);
            set_top_power(INTAKE_SPEED);
            break;

        case IntakeState::REVERSE:
            break;

        case IntakeState::EJECT:
            // Eject wrong-color ball (automatically triggered by color sort)
            // Motors reverse to push out the wrong-color ball
            // 
            // TODO: Add timing logic to automatically resume collection after ejection
            // Current implementation: Motors reverse indefinitely while EJECT state is active
            // 
            // Future improvement ideas:
            //   - Add a timer that tracks how long we've been ejecting
            //   - After a certain time (e.g., 500ms), automatically switch back to COLLECT
            //   - This way the driver doesn't need to release and re-press the intake button
            set_bottom_power(OUTTAKE_SPEED);
            set_indexer_power(OUTTAKE_SPEED);
            set_top_power(OUTTAKE_SPEED);
            break;
    }
}

// Convenience functions for autonomous
void stop() { set_target_state(IntakeState::STOP); }

void collect() { set_target_state(IntakeState::COLLECT); }

void score_long() { set_target_state(IntakeState::SCORE_LONG); }

void score_middle() { set_target_state(IntakeState::SCORE_MIDDLE); }

void reverse() { set_target_state(IntakeState::REVERSE); }

}  // namespace subsystems::intake
