#pragma once

#include <functional>
#include <string>
#include <vector>

namespace autons {

struct Auton {
    std::string Name;
    std::function<void()> auton_call;

    Auton(const std::string& name, std::function<void()> routine)
        : Name(name), auton_call(routine) {}
};


class AutonSelector {
public:
    std::vector<Auton> Autons;
    int auton_page_current;
    int auton_count;
    int last_auton_page_current;

    AutonSelector();
    AutonSelector(std::vector<Auton> autons);
    void selected_auton_call();
    void selected_auton_print();
    void autons_add(std::vector<Auton> autons);
};

// Global selector instance
extern AutonSelector auton_selector;

// Forward declaration - defined in config files
void add_autons();

// UI functions
void page_up();
void page_down();
void initialize();

}  // namespace autons

