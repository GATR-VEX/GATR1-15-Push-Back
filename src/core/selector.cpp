#include "core/selector.hpp"
#include "core/util.hpp"

#include <string>

#include "pros/rtos.hpp"
#include "pros/llemu.hpp"

#include "pros/misc.hpp"

namespace page_selector {

// Global selector instance
PageSelector selector;

void PageSelector::cleanup_util_page_task() {
    if (util_page_task != nullptr) {
        util_page_task->remove();  // Stop the task immediately
        delete util_page_task;
        util_page_task = nullptr;
    }
}

void PageSelector::selected_page_print() {
    if (page_count == 0) return;

    cleanup_util_page_task();
    
    for (int i = 0; i < 8; i++) {
        pros::lcd::clear_line(i);
    }
    pros::lcd::print(0, "Page %d/%d", page_current + 1, page_count);

    if (page_current < Autons.size()) {
        pros::lcd::print(1, "%s", Autons[page_current].name.c_str()); 
    }
    else {
         // Util page - validate index BEFORE creating task
        int util_page_index = get_util_page_index();
        
        // Validate bounds - if invalid, don't create task at all
        if (util_page_index < 0 || util_page_index >= static_cast<int>(UtilPages.size())) {
            pros::lcd::print(1, "Invalid page");
            return;
        }
        
        // Print name immediately
        pros::lcd::print(1, "%s", UtilPages[util_page_index].name.c_str());
        
        // Create task with validated index - task will just run, no checks needed
        util_page_task = new pros::Task(print_task, reinterpret_cast<void*>(util_page_index), "util_print");
    }
}


void print_task(void* param) {
   // Get the util page index from parameter (already validated before task creation)
    int util_page_index = reinterpret_cast<intptr_t>(param);
    
    // Just run - no conditional checks in the loop
    while (page_selector::selector.get_util_page_index() == util_page_index) {
        page_selector::selector.UtilPages[util_page_index].print_data();
        pros::delay(core::util::SELECTOR_DELAY_TIME); 
    }
    
    // Task exits naturally when page changes
}


void PageSelector::selected_auton_call() {
    if (page_count == 0) return;
    if (page_current >= static_cast<int>(Autons.size())) return;
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
    if (selector.page_count == 0) return;
    
    if (selector.page_current == selector.page_count - 1) {
        selector.page_current = 0;
    } else {
        selector.page_current++;
    }
    selector.selected_page_print();
}

void page_down() {

    if (selector.page_count == 0) return;
    
    if (selector.page_current == 0) {
        selector.page_current = selector.page_count - 1;
    } else {
        selector.page_current--;
    }
    selector.selected_page_print();
}

void initialize() {

    // Initialize Brain LCD
    pros::lcd::initialize();

    // Add autons from config
    add_autons();
    add_utils();
    
    // Register button callbacks for navigation
    pros::lcd::register_btn0_cb(page_down);
    pros::lcd::register_btn2_cb(page_up);
    
    // Display initial page
    selector.selected_page_print();
}

}  // namespace page_selector
