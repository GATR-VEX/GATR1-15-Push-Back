/**
 * @file selector.hpp
 * @brief Legacy brain LCD page selector (unused).
 */

#pragma once

#include <functional>
#include <string>
#include <vector>
#include "pros/rtos.hpp"

namespace page_selector {

struct Auton {
    std::string name;
    std::function<void()> auton_call;

    Auton(const std::string& name, std::function<void()> routine)
        : name(name), auton_call(routine) {}
};

struct UtilPage {
    std::string name;
    std::function<void()> print_data;

    UtilPage(const std::string& name, std::function<void()> data_function)
        : name(name), print_data(data_function) {}
};


class PageSelector {
public:
    std::vector<Auton> Autons;
    std::vector<UtilPage> UtilPages;

    int page_current = 0;
    int page_count = 0;
    pros::Task* util_page_task;
    
    PageSelector(
        std::vector<Auton> autons = {},
        std::vector<UtilPage> utils = {}
    ) :
        Autons(autons),
        UtilPages(utils)
    {
        page_count = Autons.size() + UtilPages.size();
        page_current = 0;
        util_page_task = nullptr;
    }

    void selected_auton_call();
    void selected_page_print();

    void autons_add(std::vector<Auton> autons);
    void utils_add(std::vector<UtilPage> utils);

    int get_util_page_index() {
        return page_current - static_cast<int>(Autons.size());
    }

    void cleanup_util_page_task();

};


void print_telemetry_data();

extern PageSelector selector;

void print_task(void* param);

void add_autons();
void add_utils();

void page_up();
void page_down();
void initialize();

}  // namespace page_selector
