#pragma once

#include "EZ-Template/api.hpp"
#include "core/globals.hpp"

namespace drive {

void initialize();

// Run tank control
void chassis_controller();

// Run arcade control (standard or flipped, split or single stick)
void chassis_controller(ez::e_type stick_type, bool flipped = false);

}  // namespace drive

