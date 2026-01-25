#pragma once

namespace subsystems {

namespace matchloader {
// Move matchloader up (extend piston)
void up();

// Move matchloader down (retract piston)
void down();

// Update matchloader based on controller input (call from opcontrol)
void update();
}  // namespace matchloader

namespace wing {
// Deploy wing (extend piston)
void extend();

// Retract wing (retract piston)
void retract();

// Update wing based on controller input (call from opcontrol)
void update();
}  // namespace wing

}  // namespace subsystems
