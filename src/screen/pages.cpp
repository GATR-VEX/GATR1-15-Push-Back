/**
 * @file pages.cpp
 * @brief Brain LCD debug output on blank auton selector pages.
 */

#include "screen/pages.hpp"
#include "core/subsystems/color_sort.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

#include "EZ-Template/api.hpp"
#include "pros/rtos.hpp"

#include <memory>
#include <string>

#ifdef ROBOT_BLUE
#include "core/subsystems/lever.hpp"
#endif

/**
 * Color sort debug page - displays hue, detected color, and ball presence
 */
void screen_print_color_sort_debug() {
    const double hue = color_sort::get_hue();
    const char* color_str = color_sort::get_detected_color_string();
    const bool ball_present = color_sort::is_ball_in_intake();

    const std::string line1 = "hue: " + ez::util::to_string_with_precision(hue, 1);
    const std::string line2 = "color: " + std::string(color_str);
    const std::string line3 = "ball: " + std::string(ball_present ? "yes" : "no");

    ez::screen_print(line1 + "\n" + line2 + "\n" + line3, 1);
}

#ifdef ROBOT_BLUE
/**
 * Lever debug (blank page 2): FSM state, EZ PID exit, PID error (deg), settled, motor positions.
 */
void screen_print_lever_debug() {
    using S = lever::LeverState;
    const S st = lever::get_state();

    const char* state_str = "?";
    switch (st) {
        case S::IDLE:
            state_str = "IDLE";
            break;
        case S::SCORE:
            state_str = "SCORE";
            break;
        case S::RETRACT:
            state_str = "RETRACT";
            break;
        case S::ZERO:
            state_str = "ZERO";
            break;
    }

    std::string exit_str = "n/a";
    ez::exit_output ex = ez::RUNNING;
    if (st != S::IDLE) {
        ex = lever::get_pid_exit();
        exit_str = ez::exit_to_string(ex);
    }
    const bool settled =
        (st != S::IDLE) && ex != ez::RUNNING && ex != ez::ERROR_NO_CONSTANTS;

    const double pos = globals::lever_motor.get_position();
    double err_deg = 0.0;
    if (st == S::SCORE) {
        err_deg = lever::SCORE_POSITION - pos;
    } else if (st == S::RETRACT || st == S::ZERO) {
        err_deg = lever::HOME_POSITION - pos;
    }

    const std::string line1 = std::string("state ") + state_str + "  exit " + exit_str;
    const std::string line2 = std::string("pid settled ") + (settled ? "yes" : "no");
    const std::string line_pid_err =
        st == S::IDLE ? std::string("pid err n/a")
                      : std::string("pid err ") + ez::util::to_string_with_precision(err_deg, 2);
    const std::string line3 =
        "pos deg L " + ez::util::to_string_with_precision(globals::lever_motor.get_position(0), 1) +
        "  R " + ez::util::to_string_with_precision(globals::lever_motor.get_position(1), 1);

    ez::screen_print(line1 + "\n" + line2 + "\n" + line_pid_err + "\n" + line3, 1);
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
