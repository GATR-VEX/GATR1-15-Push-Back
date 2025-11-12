#include "core/autons.hpp"

#include "core/config.hpp"
#include "core/subsystems/drive.hpp"

#ifdef ROBOT_ORANGE

namespace autons::orange {

void run_autonomous() {
    auto& chassis = subsystems::drive::chassis();
    // TODO: Replace with orange robot autonomous routine.
    chassis.moveToPose(15, 35, 90, 4000, {.horizontalDrift = 2, .lead = .3, .earlyExitRange = 4});
}

}  // namespace autons::orange

#endif

