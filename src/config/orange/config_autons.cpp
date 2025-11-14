#include "core/auton/selector.hpp"
#include "config/orange/autons.hpp"

#include <vector>

#include "core/config.hpp"

#ifdef ROBOT_ORANGE

namespace autons {

void add_autons() {
    std::vector<Auton> autons = {
        Auton("Orange Auton 1", orange::auton1),
        // Add more autons here
    };
    auton_selector.autons_add(autons);
}

}  // namespace autons

#endif

