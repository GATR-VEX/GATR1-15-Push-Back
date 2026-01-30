#include "core/config.hpp"
#include "core/subsystems/drive.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_ORANGE

namespace orange {

void auton1() {
    // TODO: Replace with orange robot autonomous routine.
    chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    chassis.pid_wait();
}
// Add more auton routines here

}  // namespace orange

#endif
