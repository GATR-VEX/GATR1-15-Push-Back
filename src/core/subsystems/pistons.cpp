#include "core/subsystems/pistons.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

namespace subsystems::pistons {

namespace indexer {

void open() {
    globals::piston_indexer.extend();
}

void close() {
    globals::piston_indexer.retract();
}

void update() {
    // TODO: Behavior desired by drivers
    if (robot::controller.get_digital(robot::Controls::wings)) {
        open();
    } else {
        close();
    }
}

}  // namespace indexer

namespace matchloader {

void up() {
    globals::piston_matchloader.extend();
}

void down() {
    globals::piston_matchloader.retract();
}

void update() {
    // TODO: Behavior desired by drivers
    if (robot::controller.get_digital(robot::Controls::ejector)) {
        up();
    } else {
        down();
    }
}

}  // namespace matchloader

namespace wings {

void extend() {
    globals::piston_wings.extend();
}

void retract() {
    globals::piston_wings.retract();
}

void update() {
    // TODO: Behavior desired by drivers
    if (robot::controller.get_digital(robot::Controls::wings)) {
        extend();
    } else {
        retract();
    }
}

}  // namespace wings

}  // namespace subsystems::pistons

