#include "core/auton/selector.hpp"

#include <string>

#include "pros/lcd.hpp"

namespace autons {

// Global selector instance
AutonSelector auton_selector;

AutonSelector::AutonSelector() {
    auton_count = 0;
    auton_page_current = 0;
    last_auton_page_current = 0;
    Autons = {};
}

AutonSelector::AutonSelector(std::vector<Auton> autons) {
    auton_count = autons.size();
    auton_page_current = 0;
    last_auton_page_current = 0;
    Autons = {};
    Autons.assign(autons.begin(), autons.end());
}

void AutonSelector::selected_auton_print() {
    if (auton_count == 0) return;
    
    for (int i = 0; i < 8; i++) {
        pros::lcd::clear_line(i);
    }
    
    pros::lcd::print(0, "Auton %d/%d", auton_page_current + 1, auton_count);
    pros::lcd::print(1, "%s", Autons[auton_page_current].Name.c_str());
}

void AutonSelector::selected_auton_call() {
    if (auton_count == 0) return;
    Autons[auton_page_current].auton_call();
}

void AutonSelector::autons_add(std::vector<Auton> autons) {
    auton_count += autons.size();
    auton_page_current = 0;
    Autons.assign(autons.begin(), autons.end());
}

// UI functions
void page_up() {
    if (auton_selector.auton_count == 0) return;
    
    if (auton_selector.auton_page_current == auton_selector.auton_count - 1) {
        auton_selector.auton_page_current = 0;
    } else {
        auton_selector.auton_page_current++;
    }
    auton_selector.selected_auton_print();
}

void page_down() {
    if (auton_selector.auton_count == 0) return;
    
    if (auton_selector.auton_page_current == 0) {
        auton_selector.auton_page_current = auton_selector.auton_count - 1;
    } else {
        auton_selector.auton_page_current--;
    }
    auton_selector.selected_auton_print();
}

void initialize() {
    // Add autons from config
    add_autons();
    
    // Register button callbacks for navigation
    pros::lcd::register_btn0_cb(page_down);
    pros::lcd::register_btn2_cb(page_up);
    
    // Display initial page
    auton_selector.selected_auton_print();
}

}  // namespace autons
