#include "core/config.hpp"
#include "core/subsystems/drive.hpp"
#include "core/subsystems/intake.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_BLUE

namespace blue {

// Auburn Car Auto
void auton1() {

    // Drive Backwards
    chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // Align with middle goal
    chassis.pid_turn_set(-45, TURN_SPEED, true);
    chassis.pid_wait();

    // Drive Backwards into middle goal
    chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    subsystems::intake::score_middle();

    // Dance

}
// Add more auton routines here

}  // namespace blue

#endif
