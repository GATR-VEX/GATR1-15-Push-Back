#pragma once

#include "lemlib/chassis/chassis.hpp"

namespace subsystems::drive {

void initialize();

void update_arcade();

lemlib::Chassis& chassis();

}  // namespace subsystems::drive

