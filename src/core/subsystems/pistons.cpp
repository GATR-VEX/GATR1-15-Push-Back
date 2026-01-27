#include "core/subsystems/pistons.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

namespace subsystems {

Piston::Piston(pros::adi::Pneumatics& piston,
               std::optional<pros::controller_digital_e_t> button,
               PistonMode mode,
               bool reversed)
    : m_piston(piston), m_button(button), m_mode(mode), m_reversed(reversed) {}

void Piston::extend() {
    m_reversed ? m_piston.retract() : m_piston.extend();
    m_extended = true;
}

void Piston::retract() {
    m_reversed ? m_piston.extend() : m_piston.retract();
    m_extended = false;
}

void Piston::toggle() {
    m_extended ? retract() : extend();
}

void Piston::update() {
    // No-op if no button assigned
    if (!m_button.has_value()) {
        return;
    }

    switch (m_mode) {
        case PistonMode::HOLD:
            if (robot::controller.get_digital(m_button.value())) {
                extend();
            } else {
                retract();
            }
            break;

        case PistonMode::TOGGLE:
            if (robot::controller.get_digital_new_press(m_button.value())) {
                toggle();
            }
            break;
    }
}

bool Piston::is_extended() const {
    return m_extended;
}

// Global piston pointers (nullptr until initialize_pistons() is called)
Piston* indexer     = nullptr;
Piston* matchloader = nullptr;
Piston* wing        = nullptr;
Piston* hood        = nullptr;

void initialize_pistons() {
    indexer     = new Piston(globals::piston_indexer); // No button - yielding control to intake subsystem
    matchloader = new Piston(globals::piston_matchloader, robot::Controls::matchloader, PistonMode::HOLD);
    wing        = new Piston(globals::piston_wing, robot::Controls::wing, PistonMode::HOLD);
    hood        = new Piston(globals::piston_hood, robot::Controls::hood, PistonMode::TOGGLE);
}

}  // namespace subsystems
