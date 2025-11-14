#include "core/auton/selector.hpp"
#include "config/blue/autons.hpp"

#include <vector>

#include "core/config.hpp"

#ifdef ROBOT_BLUE

namespace autons {

void add_autons() {
    std::vector<Auton> autons = {
        Auton("Blue Auton 1", blue::auton1),
        // Add more autons here
    };
    auton_selector.autons_add(autons);
}

}  // namespace autons

#endif

