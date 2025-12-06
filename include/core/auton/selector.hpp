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

struct Util_Page {
    std::string Name;
    std::function<std::vector<std::string>()> get_data;

    Util_Page(const std::string& name, std::function<std::vector<std::string>()> data_function)
        : Name(name), get_data(data_function) {}
};


class PageSelector {
public:
    std::vector<Auton> Autons;
    std::vector<Util_Page> Util_Pages;

    int page_current = 0;
    int auton_count = 0;
    
    PageSelector(
        std::vector<Auton> autons = {},
        std::vector<Util_Page> utils = {}
    ) :
        Autons(std::move(autons)),
        Util_Pages(std::move(utils))
    {}

    // Member functions
    void selected_auton_call();
    void selected_page_print();

    void autons_add(std::vector<Auton> autons);
    void utils_add(std::vector<Util_Page> utils);
};

// Global selector instance
extern PageSelector page_selector;

// Forward declaration - defined in config files
void add_autons();
void add_utils();

// UI functions
void page_up();
void page_down();
void initialize();

}  // namespace autons

