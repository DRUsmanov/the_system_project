#pragma once

#include <chrono>
#include <sstream>

namespace domain {

using Time = std::chrono::minutes;
using Date = std::chrono::sys_days;

/**
 * @brief Преобразует строку в дату
 * Строка должна быть задана в формате YYYY-MM-DD
 */
Date DateFromString(std::string_view date_as_str) {
    std::istringstream ss{std::string(date_as_str)};
    char separator;
    int year;
    int month;
    int day;
    ss >> year >> separator >> month >> separator >> day;
    std::chrono::year_month_day ymd{
        std::chrono::year{year},
        std::chrono::month{month}, 
        std::chrono::day{day}};
    return std::chrono::sys_days{ymd};
}

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

