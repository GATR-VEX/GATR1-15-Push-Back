#include "core/config.hpp"
#include "core/subsystems/drive.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_BLUE

namespace page_selector::blue {

void auton1() {
    auto& chassis = subsystems::drive::chassis();

    chassis.setPose(0, 0, 0);

    chassis.moveToPoint(0, 24, 10000);
    chassis.turnToHeading(180, 4000);
    chassis.moveToPoint(0, 12, 10000);


    // chassis.turnToHeading(90, 4000);
    // chassis.turnToHeading(270, 4000);
    // chassis.turnToHeading(0, 4000);

    // chassis.moveToPose(0, 15, 0, 4000, {.horizontalDrift = 2, .lead = .3, .earlyExitRange = 1});
    // chassis.moveToPose(15, 35, 90, 4000, {.horizontalDrift = 2, .lead = .3, .earlyExitRange = 4});
    // chassis.moveToPose(-8, 26, -90, 4000, {.horizontalDrift = 2, .lead = .1, .earlyExitRange = 4});
    // chassis.moveToPose(-10, 47, 0, 4000, {.horizontalDrift = 2, .lead = 0});
}
// Add more auton routines here

}  // namespace page_selector::blue

#endif
