#pragma once

#include <chrono>

namespace domain {

using Time = std::chrono::minutes;
using Date = std::chrono::sys_days;

struct TimeHasher {
    size_t operator()(const Time& time) const {
        return std::hash<std::chrono::minutes::rep>{}(time.count());
    }
};

struct DateHasher {
    size_t operator()(const Date& date) const {
        return std::hash<long long>{}(date.time_since_epoch().count());
    }
};
 
} // namespace domain

