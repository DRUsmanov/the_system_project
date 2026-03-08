#pragma once

#include <chrono>

namespace domain {

using Time = std::chrono::hh_mm_ss<std::chrono::minutes>;
using Date = std::chrono::year_month_day;
    
} // namespace domain

