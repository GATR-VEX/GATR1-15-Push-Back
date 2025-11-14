#pragma once

#if __has_include("config/robot_select.hpp")
#include "robot_select.hpp"
#endif

#if defined(ROBOT_BLUE)
#include "config/blue/config.hpp"
#elif defined(ROBOT_ORANGE)
#include "config/orange/config.hpp"
#else
#error "No robot defined! Define ROBOT_BLUE or ROBOT_ORANGE via build flag or robot_select.hpp."
#endif

