/**
 * @file screen_idle.hpp
 * @brief Idle splash screen on the brain LCD auton selector.
 *
 * After 10 s on the same selector page (while disabled), shows a centered
 * team logo from embedded RGB565 assets. Paused during competition_initialize
 * and resumed in disabled().
 */

#pragma once

namespace screen_idle {

void init();
void show_idle();
void pause();
void resume();

}  // namespace screen_idle
