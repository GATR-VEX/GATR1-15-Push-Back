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
    // Button is optional - if not provided, piston is controlled programmatically only
    // reversed: if true, hardware extend/retract is swapped to match semantic meaning
    Piston(pros::adi::Pneumatics& piston,
           std::optional<pros::controller_digital_e_t> button = std::nullopt,
           std::optional<PistonMode> mode = std::nullopt,
           bool reversed = false);

    void extend();
    void retract();
    void toggle();
    void update();  // Check controller and update state (no-op if no button assigned)
    bool is_extended() const;
    bool reversed;

private:
    pros::adi::Pneumatics& m_piston;
    std::optional<pros::controller_digital_e_t> m_button;
    std::optional<PistonMode> m_mode;
    bool m_extended = false;
};

// Initialize all pistons (call from main initialize())
void initialize();

// Safe helper functions for pistons (check nullptr before calling)
// Use these for all piston calls to maintain consistent API
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

// Global piston instances (initialized after pistons::initialize() is called)
extern std::unique_ptr<pistons::Piston> intake;
extern std::unique_ptr<pistons::Piston> matchloader;
extern std::unique_ptr<pistons::Piston> wing;
extern std::unique_ptr<pistons::Piston> gate;
extern std::unique_ptr<pistons::Piston> four_bar;

}  // namespace pistons

