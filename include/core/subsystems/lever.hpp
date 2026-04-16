#pragma once

#include <cstdint>

#include "core/config.hpp"

namespace lever {

enum class LeverState {
    IDLE,
    SCORE,
    SCORE_SLOW,
    RETURN,
    ZERO
};

void initialize();
void request_zero();
LeverState get_state();

}  // namespace lever

