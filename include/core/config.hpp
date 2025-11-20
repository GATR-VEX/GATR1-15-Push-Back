#pragma once

#if __has_include("config/robot_select.hpp")
#include "config/robot_select.hpp"
#endif

#if defined(ROBOT_BLUE)
#include "config/blue/config.hpp"
#include "config/blue/ports.hpp"
#include "config/blue/autons.hpp"
#elif defined(ROBOT_ORANGE)
#include "config/blue/config.hpp"
#include "config/blue/ports.hpp"
#include "config/blue/autons.hpp"
#else
#error "No robot defined! Define ROBOT_BLUE or ROBOT_ORANGE via build flag or robot_select.hpp."
#endif

