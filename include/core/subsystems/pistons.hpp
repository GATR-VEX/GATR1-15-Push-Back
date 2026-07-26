/**
 * @file pistons.hpp
 * @brief Pneumatic subsystem wrapper with driver HOLD/TOGGLE modes.
 */

#pragma once

#include "pros/adi.hpp"
#include "pros/misc.hpp"

#include <memory>
#include <optional>

namespace pistons {

enum class PistonMode {
    HOLD,   // Extend while button held, retract when released
    TOGGLE  // Toggle state on button press
};

class Piston {
public:
    /**
     * @param piston ADI pneumatics device
     * @param button Optional controller button; omit for programmatic-only control
     * @param mode HOLD or TOGGLE; required when button is set
     * @param reversed If true, swap hardware extend/retract vs semantic state
     */
    Piston(pros::adi::Pneumatics& piston,
           std::optional<pros::controller_digital_e_t> button = std::nullopt,
           std::optional<PistonMode> mode = std::nullopt,
           bool reversed = false);

    void extend();
    void retract();
    void toggle();
    void update();
    bool is_extended() const;
    bool reversed;

private:
    pros::adi::Pneumatics& m_piston;
    std::optional<pros::controller_digital_e_t> m_button;
    std::optional<PistonMode> m_mode;
    bool m_extended = false;
};

void initialize();

inline void safe_extend(const std::unique_ptr<Piston>& piston) {
    if (piston != nullptr) {
        piston->extend();
    }
}

inline void safe_retract(const std::unique_ptr<Piston>& piston) {
    if (piston != nullptr) {
        piston->retract();
    }
}

inline void safe_toggle(const std::unique_ptr<Piston>& piston) {
    if (piston != nullptr) {
        piston->toggle();
    }
}

inline void safe_update(const std::unique_ptr<Piston>& piston) {
    if (piston != nullptr) {
        piston->update();
    }
}

extern std::unique_ptr<pistons::Piston> intake;
extern std::unique_ptr<pistons::Piston> matchloader;
extern std::unique_ptr<pistons::Piston> wing;
extern std::unique_ptr<pistons::Piston> gate;
extern std::unique_ptr<pistons::Piston> four_bar;

}  // namespace pistons
