#include "core/subsystems/pistons.hpp"

#include "core/config.hpp"
#include "core/globals.hpp"

namespace subsystems {

namespace pistons {

Piston::Piston(pros::adi::Pneumatics& piston,
               std::optional<pros::controller_digital_e_t> button,
               PistonMode mode,
               bool reversed,
               bool default_extended)
    : m_piston(piston), m_button(button), m_mode(mode), m_reversed(reversed), m_default_extended(default_extended) {}

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
                m_default_extended ? retract() : extend();
            } else {
                m_default_extended ? extend() : retract();
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
    indexer = std::make_unique<Piston>(
        globals::piston_indexer,
        std::nullopt,
        PistonMode::HOLD,
        std::get<1>(robot::ports::PISTON_INDEXER),
        std::get<2>(robot::ports::PISTON_INDEXER));

    matchloader = std::make_unique<Piston>(
        globals::piston_matchloader,
        robot::Controls::matchloader,
        PistonMode::HOLD,
        std::get<1>(robot::ports::PISTON_MATCHLOADER),
        std::get<2>(robot::ports::PISTON_MATCHLOADER));

    wing = std::make_unique<Piston>(
        globals::piston_wing,
        robot::Controls::wing,
        PistonMode::HOLD,
        std::get<1>(robot::ports::PISTON_WING),
        std::get<2>(robot::ports::PISTON_WING));

#ifdef ROBOT_ORANGE
    hood = std::make_unique<Piston>(
        globals::piston_hood,
        robot::Controls::hood,
        PistonMode::TOGGLE,
        std::get<1>(robot::ports::PISTON_HOOD),
        std::get<2>(robot::ports::PISTON_HOOD));
#else
    hood = nullptr;  // Blue robot hood piston is not used
#endif
}

}  // namespace pistons

// Global piston pointers (nullptr until subsystems::pistons::initialize() is called)
std::unique_ptr<pistons::Piston> indexer     = nullptr;
std::unique_ptr<pistons::Piston> matchloader = nullptr;
std::unique_ptr<pistons::Piston> wing        = nullptr;
std::unique_ptr<pistons::Piston> hood        = nullptr;

}  // namespace subsystems
