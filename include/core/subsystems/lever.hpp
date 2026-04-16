#pragma once

#include <cstdint>

#include "core/config.hpp"

namespace lever {

// Lever control state machine.
enum class State {
    IDLE,
    SCORE,
    SCORE_SLOW,
    RETURN,
    ZERO
};

// Orange build doesn't have a lever hardware task; these become no-ops.
void initialize();
void request_zero();
State get_state();

}  // namespace lever

#ifdef ROBOT_BLUE
// Implementations provided in `src/core/subsystems/lever.cpp`.
#else
// Provide inline no-op implementations for non-blue builds.
namespace lever {
inline void initialize() {}
inline void request_zero() {}
inline State get_state() { return State::IDLE; }
}  // namespace lever
#endif

