#include "core/subsystems/pistons.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

namespace pistons {

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

void initialize() {
    intake = std::make_unique<Piston>(
        globals::piston_intake,
        std::nullopt,
        PistonMode::HOLD,
        robot::ports::PISTON_INTAKE_REVERSED);

    matchloader = std::make_unique<Piston>(
        globals::piston_matchloader,
        robot::Controls::matchloader,
        PistonMode::HOLD,
        robot::ports::PISTON_MATCHLOADER_REVERSED);

    wing = std::make_unique<Piston>(
        globals::piston_wing,
        robot::Controls::wing,
        PistonMode::HOLD,
        robot::ports::PISTON_WING_REVERSED);

    gate = std::make_unique<Piston>(
        globals::piston_gate,
        std::nullopt,
        PistonMode::HOLD,
        robot::ports::PISTON_GATE_REVERSED);

    four_bar = std::make_unique<Piston>(
        globals::piston_four_bar,
        robot::Controls::four_bar,
        PistonMode::HOLD,
        robot::ports::PISTON_FOUR_BAR_REVERSED);

}

// Global piston pointers (nullptr until pistons::initialize() is called)
std::unique_ptr<pistons::Piston> intake      = nullptr;
std::unique_ptr<pistons::Piston> matchloader = nullptr;
std::unique_ptr<pistons::Piston> wing        = nullptr;
std::unique_ptr<pistons::Piston> gate        = nullptr;
std::unique_ptr<pistons::Piston> four_bar    = nullptr;

}  // namespace pistons
