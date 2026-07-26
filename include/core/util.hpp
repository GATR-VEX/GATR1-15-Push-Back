/**
 * @file util.hpp
 * @brief Shared timing constants for background tasks and polling loops.
 */

#pragma once

#include <cstdint>

namespace core::util {

/** Default delay (ms) for subsystem tasks and color-sort polling. */
inline constexpr std::int32_t DELAY_TIME = 10;

/** Delay (ms) for legacy page selector UI polling. */
inline constexpr std::int32_t SELECTOR_DELAY_TIME = 50;

}  // namespace core::util
