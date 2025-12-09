#pragma once

#include <functional>
#include <string>
#include <vector>

namespace page_selector {

struct Auton {
    std::string Name;
    std::function<void()> auton_call;

    Auton(const std::string& name, std::function<void()> routine)
        : Name(name), auton_call(routine) {}
};

struct UtilPage {
    std::string Name;
    std::function<void()> print_data;

    UtilPage(const std::string& name, std::function<void()> data_function)
        : Name(name), print_data(data_function) {}
};


class PageSelector {
public:
    std::vector<Auton> Autons;
    std::vector<UtilPage> UtilPages;

    int page_current = 0;
    int page_count = 0;
    
    PageSelector(
        std::vector<Auton> autons = {},
        std::vector<UtilPage> utils = {}
    ) :
        Autons(autons),
        UtilPages(utils)
    {
        page_count = Autons.size() + UtilPages.size();
        page_current = 0;
    }

    // Member functions
    void selected_auton_call();
    void selected_page_print();

    void autons_add(std::vector<Auton> autons);
    void utils_add(std::vector<UtilPage> utils);
};


// Definitions of utility functions
void print_telemetry_data();


// Global selector instance
extern PageSelector selector_;

void print_task(void* param);

// Forward declaration - defined in config files
void add_autons();
void add_utils();

// UI functions
void page_up();
void page_down();
void initialize();

}  // namespace page_selector

