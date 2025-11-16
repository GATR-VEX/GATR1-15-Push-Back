#include "core/subsystems/color_sort.hpp"
#include "core/globals.hpp"
#include "core/config.hpp"

#include <cmath>
#include <cstring>

namespace subsystems::color_sort {

double get_current_hue() {
    return globals::optical_color_sort.get_hue();
}

bool is_color_blue(double hue) {
    // Check if hue is in blue range (COLOR_BLUE_HUE_MIN to COLOR_BLUE_HUE_MAX)
    return hue >= COLOR_BLUE_HUE_MIN && hue <= COLOR_BLUE_HUE_MAX;
}

bool is_color_red(double hue) {
    // Check if hue is in red range (COLOR_RED_HUE_MIN to COLOR_RED_HUE_MAX, or wraps around)
    // Red can wrap around 360/0, so check both ranges
    bool in_normal_range = hue >= COLOR_RED_HUE_MIN && hue <= COLOR_RED_HUE_MAX;
    bool in_wrap_range = hue >= COLOR_RED_HUE_WRAP_MIN || hue <= COLOR_RED_HUE_MAX;
    return in_normal_range || in_wrap_range;
}

bool is_wrong_color_detected() {
    // Read optical sensor hue value
    double hue = get_current_hue();
}

}  // namespace subsystems::color_sort

