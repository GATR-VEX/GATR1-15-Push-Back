#include "core/subsystems/comp_timer.hpp"
#include "core/config.hpp"
#include "core/util.hpp"

#include "pros/rtos.hpp"

namespace subsystems::comp_timer {

static std::uint32_t match_start_time = 0;
static std::uint32_t last_buzzed_second = UINT32_MAX;

void initialize() {
    match_start_time = pros::millis();
    last_buzzed_second = UINT32_MAX;  // Reset so we can buzz at 20s
}

void update() {
    // Only run if enabled in config and competition is connected
    if (!robot::ENABLE_COMP_TIMER &&
        !pros::competition::is_connected()) {
        return;
    }

    // Calculate elapsed time and remaining time
    std::uint32_t elapsed_time = pros::millis() - match_start_time;
    
    // Don't do anything if match hasn't started or is already over
    if (elapsed_time >= DRIVER_CONTROL_TIME_MS) {
        return;
    }

    std::uint32_t remaining_time = DRIVER_CONTROL_TIME_MS - elapsed_time;
    // Use ceiling so we buzz at 20.0s, 10.0s, etc. (not ~0.9s early with truncation)
    std::uint32_t remaining_seconds = (remaining_time + 999) / 1000;

    // Skip if we've already buzzed for this second
    if (last_buzzed_second == remaining_seconds) {
        return;
    }

    // Triple buzz at 20 seconds remaining
    if (remaining_seconds == 20) {
        robot::controller.rumble("...");
        last_buzzed_second = 20;
        return;
    }

    // Countdown buzz every second from 10 seconds to 4 seconds
    if (remaining_seconds >= 4 && remaining_seconds <= 10) {
        robot::controller.rumble(".");
        last_buzzed_second = remaining_seconds;
        return;
    }

    // Double buzz for last 3 seconds (3, 2, 1)
    if (remaining_seconds >= 1 && remaining_seconds <= 3) {
        robot::controller.rumble("..");  // Double buzz
        last_buzzed_second = remaining_seconds;
        return;
    }
}

}  // namespace subsystems::comp_timer
