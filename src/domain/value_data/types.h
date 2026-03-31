#pragma once

#include <chrono>

namespace domain {

using Time = std::chrono::hh_mm_ss<std::chrono::minutes>;
using Date = std::chrono::year_month_day;

struct TimeHasher {
    size_t operator()(const Time& time) const {
        return std::hash<std::chrono::minutes::rep>{}(time.to_duration().count());
    }
};

struct DateHasher {
    size_t operator()(const Date& date) const {
        auto days = std::chrono::sys_days{date};
        return std::hash<long long>{}(days.time_since_epoch().count());
    }
};
 
} // namespace domain

