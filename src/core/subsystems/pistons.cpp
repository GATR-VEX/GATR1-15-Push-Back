#include "core/subsystems/pistons.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

namespace subsystems {

namespace matchloader {

void up() {
    globals::piston_matchloader.extend();
}

void down() {
    globals::piston_matchloader.retract();
}

void update() {
    if (robot::controller.get_digital(robot::Controls::ejector)) {
        up();
    } else {
        down();
    }
}

}  // namespace matchloader

namespace wing {

void extend() {
    globals::piston_wing.extend();
}

void retract() {
    globals::piston_wing.retract();
}

void update() {
    if (robot::controller.get_digital(robot::Controls::wing)) {
        extend();
    } else {
        retract();
    }
}

}  // namespace wing

}  // namespace subsystems
