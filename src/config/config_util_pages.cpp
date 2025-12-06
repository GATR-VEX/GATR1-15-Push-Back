#include <vector>
#include "core/auton/selector.hpp"

#include "config/util_pages.hpp"

#include <vector>

#include "core/config.hpp"

namespace page_selector {
    
    void add_utils() {
        std::vector<Util_Page> util_pages = {
            Util_Page("Telemetry", get_telemtry_data),
            // Add more autons here
        };
        page_selector.utils_add(util_pages);
}    
} // namespace page_selector
