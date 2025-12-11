#include "core/selector.hpp"
#include "config/orange/autons.hpp"

#include <vector>

#include "core/config.hpp"

#ifdef ROBOT_ORANGE

namespace page_selector {

void add_autons() {
    std::vector<Auton> autons = {
        Auton("Orange Auton 1", orange::auton1),
        // Add more autons here
    };
    selector_.autons_add(autons);
}

}  // namespace page_selector

#endif

