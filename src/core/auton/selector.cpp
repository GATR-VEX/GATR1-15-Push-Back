#include "core/auton/selector.hpp"
#include "core/util.hpp"

#include <string>

#include "pros/rtos.hpp"
#include "pros/llemu.hpp"

namespace page_selector {

// Global selector instance
PageSelector page_selector;

PageSelector::PageSelector(std::vector<Auton> autons, std::vector<Util_Page> utils) {
    auton_count = autons.size();
    page_current = 0;
    Autons = {};
    Util_Pages = {};

    Autons.assign(autons.begin(), autons.end());
    Util_Pages.assign(utils.begin(), utils.end());
}

void PageSelector::selected_page_print() {
    if (auton_count == 0) return;
    
    for (int i = 0; i < 8; i++) {
        pros::lcd::clear_line(i);
    }
    if (page_current > auton_count) {
        pros::lcd::print(0, "Auton %d/%d", page_current + 1, auton_count);
        pros::lcd::print(1, "%s", Autons[page_current].Name.c_str()); 
    }
    else {
        int util_page = page_current;
        while (page_current == util_page) {
            pros::lcd::print(0, "%s", Util_Pages[util_page].Name.c_str());
            Util_Pages[util_page].get_data();

            pros::delay(core::util::DELAY_TIME);
        }
    }
}

void PageSelector::selected_auton_call() {
    if (auton_count == 0) return;
    Autons[page_current].auton_call();
}

void PageSelector::autons_add(std::vector<Auton> autons) {
    auton_count += autons.size();
    page_current = 0;
    Autons.assign(autons.begin(), autons.end());
}

void PageSelector::utils_add(std::vector<Util_Page> utils) {
    Util_Pages.assign(utils.begin(), utils.end());
}

// UI functions
void page_up() {
    if (page_selector.auton_count == 0) return;
    
    if (page_selector.page_current == page_selector.auton_count - 1) {
        page_selector.page_current = 0;
    } else {
        page_selector.page_current++;
    }
    page_selector.selected_page_print();
}

void page_down() {
    if (page_selector.auton_count == 0) return;
    
    if (page_selector.page_current == 0) {
        page_selector.page_current = page_selector.auton_count - 1;
    } else {
        page_selector.page_current--;
    }
    page_selector.selected_page_print();
}

void initialize() {
    // Add autons from config
    add_autons();
    add_utils();

    
    // Register button callbacks for navigation
    pros::lcd::register_btn0_cb(page_down);
    pros::lcd::register_btn2_cb(page_up);
    
    // Display initial page
    page_selector.selected_page_print();
}

}  // namespace page_selector
