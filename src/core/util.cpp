#include "core/util.hpp"

#include "pros/lcd.hpp"

namespace core::util {

void start_telemetry_task() { pros::lcd::initialize(); }

}  // namespace core::util

