#pragma once

#include <chrono>
#include <optional>

namespace domain {

struct Date {
    std::chrono::year year;
    std::chrono::month month;
    std::chrono::day day;

    auto operator<=>(const Date&) const = default;
};

struct Time {
    std::chrono::hours hours;
    std::chrono::minutes minutes;

    auto operator<=>(const Time&) const = default;
};

} // namespace domain
