#pragma once

#include "core/subsystems/color_sort.hpp"

void default_constants();
void add_autons();

namespace blue {

void match_auton(subsystems::color_sort::Color color);
void match_auton_blue();
void match_auton_red();

void elims_auton(subsystems::color_sort::Color color);
void elims_auton_blue();
void elims_auton_red();

void pid_tuning_auton();
void skills_auton();

}  // namespace blue

