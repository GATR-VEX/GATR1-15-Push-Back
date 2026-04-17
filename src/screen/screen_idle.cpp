#include "screen/screen_idle.hpp"

// Same robot selection as core/config.hpp; this TU does not include config.hpp, so pull in the macro here.
#if __has_include("config/robot_select.hpp")
#include "config/robot_select.hpp"
#endif

#ifdef ROBOT_BLUE
#define GATR_VEX_BLUE_IMPLEMENTATION
#include "screen/assets/gatr_vex_blue.hpp"
#endif

#ifdef ROBOT_ORANGE
#define GATR_VEX_ORANGE_IMPLEMENTATION
#include "screen/assets/gatr_vex_orange.hpp"
#endif

#include "liblvgl/draw/lv_image_dsc.h"
#include "liblvgl/misc/lv_color.h"

#include "EZ-Template/api.hpp"
#include "pros/colors.hpp"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

static volatile bool g_paused = false;

static constexpr int kScreenW = 480;
static constexpr int kScreenH = 272;

namespace screen_idle {

void show_idle();

namespace {

constexpr std::uint32_t kIdleMs = 10000;
constexpr int kPollMs = 50;
/** Nearest-neighbor upscale from embedded RGB565; >1 zooms in (center crop) so the logo reads larger. */
constexpr float kIdleLogoScale = 1.9f;
/** Pixels of black border so the image is not flush to the screen edge. */
constexpr int kIdleLogoMarginPx = 8;
/** Positive shifts the idle logo down from vertical center (clamped to stay on-screen). */
constexpr int kIdleLogoOffsetYPx = 25;
/**
 * Square LVGL export with a wide logo: ignore empty top/bottom padding in the source (fraction of height).
 * Increase these if the art sits lower/higher; set both to 0 to use the full 272×272.
 */
constexpr float kIdleSourceCropTopFrac = 0.22f;
constexpr float kIdleSourceCropBottomFrac = 0.22f;

std::vector<std::uint32_t> g_cached_px;
unsigned g_cached_w = 0;
unsigned g_cached_h = 0;
bool g_cache_ok = false;
/** After we show idle for the current page, do not redraw until the page changes (avoids full refresh every kIdleMs). */
bool g_idle_shown_for_current_page = false;

static std::uint32_t rgb565_to_screen(std::uint16_t p) {
    const unsigned r5 = (p >> 11) & 0x1Fu;
    const unsigned g6 = (p >> 5) & 0x3Fu;
    const unsigned b5 = p & 0x1Fu;
    const unsigned r = (r5 * 255u + 15u) / 31u;
    const unsigned g = (g6 * 255u + 31u) / 63u;
    const unsigned b = (b5 * 255u + 15u) / 31u;
    return 0x00000000u | (static_cast<std::uint32_t>(r) << 16) |
           (static_cast<std::uint32_t>(g) << 8) | static_cast<std::uint32_t>(b);
}

static bool build_idle_logo_cache() {
    if (g_cache_ok) {
        return true;
    }
#if !defined(ROBOT_BLUE) && !defined(ROBOT_ORANGE)
    return false;
#else
#if defined(ROBOT_BLUE)
    const lv_image_dsc_t& dsc = GatrVexBlue;
#else
    const lv_image_dsc_t& dsc = GatrVexOrange;
#endif
    if (dsc.header.cf != LV_COLOR_FORMAT_RGB565 || dsc.data == nullptr) {
        return false;
    }
    const unsigned iw = dsc.header.w;
    const unsigned ih = dsc.header.h;
    if (iw == 0 || ih == 0) {
        return false;
    }
    const unsigned row_stride =
        dsc.header.stride != 0 ? static_cast<unsigned>(dsc.header.stride) : iw * 2u;

    unsigned y0 = static_cast<unsigned>(static_cast<float>(ih) * kIdleSourceCropTopFrac);
    unsigned y1 = ih - static_cast<unsigned>(static_cast<float>(ih) * kIdleSourceCropBottomFrac);
    if (y1 <= y0 || y0 >= ih) {
        y0 = 0;
        y1 = ih;
    }
    const unsigned ih_use = y1 - y0;

    const unsigned sw = static_cast<unsigned>(static_cast<float>(iw) * kIdleLogoScale + 0.5f);
    const unsigned sh = static_cast<unsigned>(static_cast<float>(ih_use) * kIdleLogoScale + 0.5f);
    if (sw == 0 || sh == 0) {
        return false;
    }
    const int max_w = kScreenW - 2 * kIdleLogoMarginPx;
    const int max_h = kScreenH - 2 * kIdleLogoMarginPx;
    if (max_w <= 0 || max_h <= 0) {
        return false;
    }
    const unsigned crop_w = std::min({sw, static_cast<unsigned>(max_w), static_cast<unsigned>(kScreenW)});
    const unsigned crop_h = std::min({sh, static_cast<unsigned>(max_h), static_cast<unsigned>(kScreenH)});
    const unsigned sx0 = (sw - crop_w) / 2u;
    const unsigned sy0 = (sh - crop_h) / 2u;

    g_cached_px.resize(static_cast<size_t>(crop_w) * crop_h);
    const std::uint8_t* data = dsc.data;
    for (unsigned dy = 0; dy < crop_h; ++dy) {
        for (unsigned dx = 0; dx < crop_w; ++dx) {
            const unsigned ssx = sx0 + dx;
            const unsigned ssy = sy0 + dy;
            const std::uint64_t src_x =
                std::min(static_cast<std::uint64_t>(ssx) * static_cast<std::uint64_t>(iw) / static_cast<std::uint64_t>(sw),
                         static_cast<std::uint64_t>(iw - 1));
            const std::uint64_t src_y_off =
                std::min(static_cast<std::uint64_t>(ssy) * static_cast<std::uint64_t>(ih_use) / static_cast<std::uint64_t>(sh),
                         static_cast<std::uint64_t>(ih_use - 1));
            const std::uint64_t src_y = static_cast<std::uint64_t>(y0) + src_y_off;
            const size_t off =
                static_cast<size_t>(src_y) * row_stride + static_cast<size_t>(src_x) * 2u;
            const std::uint16_t p =
                static_cast<std::uint16_t>(data[off]) | (static_cast<std::uint16_t>(data[off + 1]) << 8);
            g_cached_px[static_cast<size_t>(dy) * crop_w + dx] = rgb565_to_screen(p);
        }
    }
    g_cached_w = crop_w;
    g_cached_h = crop_h;
    g_cache_ok = true;
    return true;
#endif
}

void task_fn() {
    int last_page = ez::as::auton_selector.auton_page_current;
    std::uint32_t last_switch = pros::millis();
    bool was_paused = false;

    while (true) {
        const bool p = g_paused;
        if (was_paused && !p) {
            last_switch = pros::millis();
            last_page = ez::as::auton_selector.auton_page_current;
        }
        was_paused = p;

        if (!p) {
            const int page = ez::as::auton_selector.auton_page_current;
            const std::uint32_t now = pros::millis();
            if (page != last_page) {
                last_page = page;
                last_switch = now;
                g_idle_shown_for_current_page = false;
            } else if (!g_idle_shown_for_current_page && now - last_switch >= kIdleMs &&
                       ez::as::page_blank_current() < 0) {
                show_idle();
            }
        }
        pros::delay(kPollMs);
    }
}

std::unique_ptr<pros::Task> g_task;

}  // namespace

void show_idle() {
    pros::screen::set_pen(pros::Color::black);
    pros::screen::fill_rect(0, 0, kScreenW, kScreenH);
    if (!build_idle_logo_cache()) {
        g_idle_shown_for_current_page = true;
        return;
    }
    const int x0 = (kScreenW - static_cast<int>(g_cached_w)) / 2;
    const int h = static_cast<int>(g_cached_h);
    const int max_y0 = kScreenH - h;
    int y0 = (max_y0 / 2) + kIdleLogoOffsetYPx;
    if (y0 < 0) {
        y0 = 0;
    } else if (y0 > max_y0) {
        y0 = max_y0;
    }
    const int x1 = x0 + static_cast<int>(g_cached_w) - 1;
    const int y1 = y0 + h - 1;
    pros::screen::copy_area(x0, y0, x1, y1, g_cached_px.data(), static_cast<std::int32_t>(g_cached_w));
    g_idle_shown_for_current_page = true;
}

void pause() { g_paused = true; }

void resume() { g_paused = false; }

void init() { g_task = std::make_unique<pros::Task>(task_fn); }

}  // namespace screen_idle
