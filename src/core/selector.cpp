#include "core/selector.hpp"
#include "core/util.hpp"

#include <string>

#include "pros/rtos.hpp"
#include "pros/llemu.hpp"

#include "pros/misc.hpp"

namespace page_selector {

// Global selector instance
PageSelector selector_;


void PageSelector::selected_page_print() {
    if (page_count == 0) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        pros::lcd::clear_line(i);
    }
    pros::lcd::print(0, "Page %d/%d", page_current + 1, page_count);

    if (page_current < Autons.size()) {
        pros::lcd::print(1, "%s", Autons[page_current].Name.c_str()); 
    }
    else {
        pros::Task util_page_print_task(print_task, nullptr, "print");
        pros::delay(core::util::DELAY_TIME);
    }
}


void print_task(void* param) {
    int util_page = page_selector::selector_.page_current - page_selector::selector_.Autons.size();

    pros::lcd::print(1, "%s", page_selector::selector_.UtilPages[util_page].Name.c_str());


    while (page_selector::selector_.page_current - page_selector::selector_.Autons.size() == util_page) {
        page_selector::selector_.UtilPages[util_page].print_data();

        pros::delay(50); 
    }
}


void PageSelector::selected_auton_call() {
    if (page_count == 0) return;
    if (page_count > Autons.size()) return;
    Autons[page_current].auton_call();
}

void PageSelector::autons_add(std::vector<Auton> autons) {
    page_count += autons.size();
    Autons.assign(autons.begin(), autons.end());
}

void PageSelector::utils_add(std::vector<UtilPage> utils) {
    page_count += utils.size();
    UtilPages.assign(utils.begin(), utils.end());
}

// UI functions
void page_up() {
    if (selector_.page_count == 0) return;
    
    if (selector_.page_current == selector_.page_count - 1) {
        selector_.page_current = 0;
    } else {
        selector_.page_current++;
    }
    selector_.selected_page_print();
}

void page_down() {

    if (selector_.page_count == 0) return;
    
    if (selector_.page_current == 0) {
        selector_.page_current = selector_.page_count - 1;
    } else {
        selector_.page_current--;
    }
    selector_.selected_page_print();
}

void initialize() {
    // Add autons from config
    add_autons();
    add_utils();


    
    // Register button callbacks for navigation
    pros::lcd::register_btn0_cb(page_down);
    pros::lcd::register_btn2_cb(page_up);
    
    // Display initial page
    selector_.selected_page_print();
}

}  // namespace page_selector
