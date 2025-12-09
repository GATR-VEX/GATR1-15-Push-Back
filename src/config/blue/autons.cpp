#include "core/config.hpp"
#include "core/subsystems/drive.hpp"

#include "pros/llemu.hpp"


#ifdef ROBOT_BLUE

namespace page_selector::blue {

void auton1() {
    //auto& chassis = subsystems::drive::chassis();

    //pros::delay(100000);

    // chassis.moveToPose(15, 35, 90, 4000, {.horizontalDrift = 2, .lead = .3, .earlyExitRange = 4});
    // chassis.moveToPose(-8, 26, -90, 4000, {.horizontalDrift = 2, .lead = .1, .earlyExitRange = 4});
    // chassis.moveToPose(-10, 47, 0, 4000, {.horizontalDrift = 2, .lead = 0});
}

void auton2() {
    //auto& chassis = subsystems::drive::chassis();
}
// Add more auton routines here

}  // namespace autons::blue

#endif
