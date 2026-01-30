#include "core/config.hpp"
#include "core/subsystems/drive.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_BLUE

namespace blue {

void auton1() {
    chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    chassis.pid_wait();
  
    chassis.pid_drive_set(-12_in, DRIVE_SPEED);
    chassis.pid_wait();
  
    chassis.pid_drive_set(-12_in, DRIVE_SPEED);
    chassis.pid_wait();
}
// Add more auton routines here

}  // namespace blue

#endif
