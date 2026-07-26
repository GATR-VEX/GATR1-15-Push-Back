/**
 * @file drive.hpp
 * @brief EZ-Template chassis initialization and operator drive modes.
 */

#pragma once

#include "EZ-Template/api.hpp"
#include "core/globals.hpp"

namespace drive {

/** Configure curves, PID defaults, and initialize the EZ-Template chassis. */
void initialize();

/** Tank drive using left/right joysticks. */
void chassis_controller();

/**
 * Arcade drive (standard or flipped stick layout).
 * @param stick_type ez::SPLIT (left = turn, right = throttle) or ez::SINGLE
 * @param flipped If true, use flipped arcade mapping
 */
void chassis_controller(ez::e_type stick_type, bool flipped = false);

}  // namespace drive
