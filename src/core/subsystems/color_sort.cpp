#include "core/subsystems/color_sort.hpp"
#include "core/globals.hpp"
#include "core/util.hpp"

#include "pros/rtos.hpp"

namespace subsystems::color_sort {

double get_hue() {
    return globals::optical_color_sort.get_hue();
}

bool is_color(Color color) {
    double hue = get_hue();

    switch (color) {
        case Color::BLUE:
            return hue >= BLUE_HUE_MIN && hue <= BLUE_HUE_MAX;

        case Color::RED:
            // Red wraps around 360, so check both ranges
            return (hue >= RED_HUE_WRAP) || (hue <= RED_HUE_MAX);
    }

    return false;
}

bool wait_for_color(Color color, std::uint32_t timeout_ms) {
    std::uint32_t start_time = pros::millis();

    while (pros::millis() - start_time < timeout_ms) {
        if (is_color(color)) {
            return true;
        }
        pros::delay(core::util::DELAY_TIME);
    }

    return false;  // Timeout
}

bool is_ball_in_intake() {
    auto proximity = globals::optical_color_sort.get_proximity();
    return proximity != PROS_ERR && proximity >= BALL_PROXIMITY_THRESHOLD;
}

bool wait_for_ball(std::uint32_t timeout_ms) {
    std::uint32_t start_time = pros::millis();

    while (pros::millis() - start_time < timeout_ms) {
        if (is_ball_in_intake())
            return true;
        pros::delay(core::util::DELAY_TIME);
    }

    return false;  // Timeout
}

const char* get_detected_color_string() {
    if (is_color(Color::RED))
        return "RED";
    if (is_color(Color::BLUE))
        return "BLUE";
    return "none";
}

}  // namespace subsystems::color_sort
