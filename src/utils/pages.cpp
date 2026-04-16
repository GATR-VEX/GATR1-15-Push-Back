#include "core/utils/pages.hpp"
#include "core/subsystems/color_sort.hpp"
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

namespace utils_pages {

static std::unique_ptr<pros::Task> debug_screen_task;

void debug_screen_task_fn() {
    while (true) {
        if (!pros::competition::is_connected()) {
            if (ez::as::page_blank_is_on(0)) {
                screen_print_color_sort_debug();
            }
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
