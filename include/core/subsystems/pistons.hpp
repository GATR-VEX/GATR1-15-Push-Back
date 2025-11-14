#pragma once

namespace subsystems::pistons {

namespace indexer {
// Open indexer (extend piston)
void open();

// Close indexer (retract piston)
void close();

// Update indexer based on controller input (call from opcontrol)
void update();
}  // namespace indexer

namespace matchloader {
// Move matchloader up (extend piston)
void up();

// Move matchloader down (retract piston)
void down();

// Update matchloader based on controller input (call from opcontrol)
void update();
}  // namespace matchloader

namespace wings {
// Deploy wings (extend piston)
void extend();

// Retract wings (retract piston)
void retract();

// Update wings based on controller input (call from opcontrol)
void update();
}  // namespace wings

}  // namespace subsystems::pistons

