#include <vector>
#include "core/selector.hpp"

#include <vector>

#include "core/config.hpp"

namespace page_selector {
    
    void add_utils() {
        std::vector<UtilPage> util_pages = {
            UtilPage("Telemetry", print_telemetry_data),
            // Add more util pages here
        };
        selector_.utils_add(util_pages);
}    
} // namespace page_selector
