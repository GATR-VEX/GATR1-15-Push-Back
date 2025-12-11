#include "core/config.hpp"
#include "core/subsystems/drive.hpp"

#include "pros/llemu.hpp"

#ifdef ROBOT_ORANGE

namespace page_selector::orange {

void auton1() {
    auto& chassis = subsystems::drive::chassis();
    // TODO: Replace with orange robot autonomous routine.
    pros::lcd::set_text(4, "Orange Auton 2");
}
// Add more auton routines here

}  // namespace page_selector::orange

#endif
