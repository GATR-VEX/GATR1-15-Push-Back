#pragma once

// Blue bot intake state machine.
enum class IntakeState {
    STOP,
    SCORE_LONG,
    SCORE_SLOW,
    SCORE_MIDDLE,
    COLLECT,
    REVERSE,
    REVERSE_SLOW,
};

