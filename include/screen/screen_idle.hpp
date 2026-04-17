#pragma once

namespace screen_idle {

void init();
/** Black screen + centered crop of embedded LVGL RGB565 asset (GatrVexBlue). */
void show_idle();
void pause();
void resume();

}  // namespace screen_idle
