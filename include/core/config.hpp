/**
 * @file config.hpp
 * @brief Compile-time robot selection and per-robot configuration includes.
 *
 * Defines either ROBOT_BLUE or ROBOT_ORANGE via build flag (-DROBOT_BLUE) or
 * include/config/robot_select.hpp, then pulls in that robot's config, ports,
 * and auton declarations. The build fails if no robot is selected.
 */

#pragma once

// Include robot_select.hpp if it exists to define ROBOT_BLUE or ROBOT_ORANGE
#if __has_include("config/robot_select.hpp")
#include "config/robot_select.hpp"
#endif

#if defined(ROBOT_BLUE)
#include "config/blue/config.hpp"
#include "config/blue/ports.hpp"
#include "config/blue/autons.hpp"
#elif defined(ROBOT_ORANGE)
#include "config/orange/config.hpp"
#include "config/orange/ports.hpp"
#include "config/orange/autons.hpp"
#else
#error "No robot defined! Define ROBOT_BLUE or ROBOT_ORANGE via build flag or robot_select.hpp."
#endif
