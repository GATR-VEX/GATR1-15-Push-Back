#include "screen/pages.hpp"
#include "core/subsystems/color_sort.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

#include "EZ-Template/api.hpp"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"

#include <memory>
#include <string>

/**
 * Color sort debug page - displays hue, detected color, and ball presence
 */
void screen_print_color_sort_debug() {
    double hue = color_sort::get_hue();
    const char* color_str = color_sort::get_detected_color_string();
    bool ball_present = color_sort::is_ball_in_intake();

    std::string line1 = "hue: " + ez::util::to_string_with_precision(hue, 1);
    std::string line2 = "color: " + std::string(color_str);
    std::string line3 = "ball: " + std::string(ball_present ? "yes" : "no");

    ez::screen_print(line1 + "\n" + line2 + "\n" + line3, 1);
}

#ifdef ROBOT_BLUE
/**
 * Lever debug (blank page 2): raw motor positions (deg) and velocities.
 * Navigate past autons to blank pages; use the page after the color-sort blank page.
 */
void screen_print_lever_debug() {
    const double p0 = globals::lever_motor.get_position(0);
    const double p1 = globals::lever_motor.get_position(1);
    const double v0 = globals::lever_motor.get_actual_velocity(0);
    const double v1 = globals::lever_motor.get_actual_velocity(1);

    std::string line1 = "pos deg L " + ez::util::to_string_with_precision(p0, 1) + "  R " +
                        ez::util::to_string_with_precision(p1, 1);
    std::string line2 = "vel L " + ez::util::to_string_with_precision(v0, 0) + "  R " +
                        ez::util::to_string_with_precision(v1, 0);
    std::string line3 = "lever dbg";

    ez::screen_print(line1 + "\n" + line2 + "\n" + line3, 1);
}
#endif

namespace utils_pages {

static std::unique_ptr<pros::Task> debug_screen_task;

void debug_screen_task_fn() {
    while (true) {
        if (!pros::competition::is_connected()) {
#if defined(ROBOT_BLUE)
            if (ez::as::page_blank_is_on(0)) {
                screen_print_color_sort_debug();
            } else if (ez::as::page_blank_is_on(1)) {
                screen_print_lever_debug();
            }
#else
            if (ez::as::page_blank_is_on(0)) {
                screen_print_color_sort_debug();
            }
#endif
        } else {
            if (ez::as::page_blank_amount() > 0)
                ez::as::page_blank_remove_all();
        }

        pros::delay(ez::util::DELAY_TIME);
    }
}

void initialize() {
    debug_screen_task = std::make_unique<pros::Task>(debug_screen_task_fn);
}

}  // namespace utils_pages
