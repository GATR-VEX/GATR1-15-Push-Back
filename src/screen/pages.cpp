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
#include "core/subsystems/lever.hpp"

namespace {

const char* lever_fsm_state_cstr(lever::LeverState s) {
    switch (s) {
        case lever::LeverState::IDLE:
            return "IDLE";
        case lever::LeverState::SCORE:
            return "SCORE";
        case lever::LeverState::RETRACT:
            return "RETRACT";
        case lever::LeverState::ZERO:
            return "ZERO";
    }
    return "?";
}

std::string lever_debug_pid_exit_string() {
    if (lever::get_state() == lever::LeverState::IDLE) {
        return "n/a";
    }
    return ez::exit_to_string(lever::get_pid_exit());
}

bool lever_debug_pid_exit_settled() {
    if (lever::get_state() == lever::LeverState::IDLE) {
        return false;
    }
    const ez::exit_output ex = lever::get_pid_exit();
    return ex != ez::RUNNING && ex != ez::ERROR_NO_CONSTANTS;
}

}  // namespace

/**
 * Lever debug (blank page 2): FSM state, EZ PID exit, motor positions (deg).
 */
void screen_print_lever_debug() {
    const double p0 = globals::lever_motor.get_position(0);
    const double p1 = globals::lever_motor.get_position(1);

    const std::string line1 = std::string("state ") + lever_fsm_state_cstr(lever::get_state()) +
                              "  exit " + lever_debug_pid_exit_string();
    const std::string line2 =
        std::string("pid settled ") + (lever_debug_pid_exit_settled() ? "yes" : "no");
    const std::string line3 = "pos deg L " + ez::util::to_string_with_precision(p0, 1) + "  R " +
                              ez::util::to_string_with_precision(p1, 1);

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
