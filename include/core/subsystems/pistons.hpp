#pragma once

#include "pros/adi.hpp"
#include "pros/misc.hpp"

#include <optional>

namespace subsystems {

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
           PistonMode mode = PistonMode::HOLD,
           bool default_extended = false,
           bool reversed = false);

    void extend();
    void retract();
    void toggle();
    void update();  // Check controller and update state (no-op if no button assigned)
    void set_default_state();  // Apply the default state to the piston
    bool is_extended() const;

private:
    pros::adi::Pneumatics& m_piston;
    std::optional<pros::controller_digital_e_t> m_button;
    PistonMode m_mode;
    bool m_extended;
    bool m_default_extended;
    bool m_reversed;
};

// Initialize all pistons (call from main initialize())
void initialize_pistons();

// Global piston instances (initialized after initialize_pistons() is called)
extern Piston* indexer;
extern Piston* matchloader;
extern Piston* wing;
extern Piston* hood;

}  // namespace subsystems
