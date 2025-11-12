#include "core/autons.hpp"

#include "core/config.hpp"
#include "core/subsystems/drive.hpp"

#ifdef ROBOT_BLUE

namespace autons::blue {

void run_autonomous() {
    auto& chassis = subsystems::drive::chassis();
    chassis.moveToPose(15, 35, 90, 4000, {.horizontalDrift = 2, .lead = .3, .earlyExitRange = 4});
    chassis.moveToPose(-8, 26, -90, 4000, {.horizontalDrift = 2, .lead = .1, .earlyExitRange = 4});
    chassis.moveToPose(-10, 47, 0, 4000, {.horizontalDrift = 2, .lead = 0});
}

}  // namespace autons::blue

#endif

