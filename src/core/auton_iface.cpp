#include "core/autons.hpp"

#include "core/config.hpp"

namespace autons {

#if defined(ROBOT_BLUE)
    namespace blue {
    void run_autonomous();
    }  // namespace blue

    void run_autonomous() { blue::run_autonomous(); }
#elif defined(ROBOT_ORANGE)
    namespace orange {
    void run_autonomous();
    }  // namespace orange

    void run_autonomous() { orange::run_autonomous(); }
#endif

}  // namespace autons

