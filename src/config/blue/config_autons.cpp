#include "core/selector.hpp"
#include "config/blue/autons.hpp"

#include <vector>

#include "core/config.hpp"

#ifdef ROBOT_BLUE

namespace page_selector {

void add_autons() {
    std::vector<Auton> autons = {
        Auton("Blue Auton 1", blue::auton1),
        Auton("Blue Auton 2", blue::auton2),

        // Add more autons here
    };
    selector_.autons_add(autons);
}



}  // namespace pager_selector

#endif

