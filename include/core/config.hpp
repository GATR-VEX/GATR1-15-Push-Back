#pragma once

#if __has_include("robot_select.hpp")
#include "robot_select.hpp"
#endif

#if defined(ROBOT_BLUE)
#include "blue_config.hpp"
#elif defined(ROBOT_ORANGE)
#include "orange_config.hpp"
#else
#error "No robot defined! Define ROBOT_BLUE or ROBOT_ORANGE via build flag or robot_select.hpp."
#endif

