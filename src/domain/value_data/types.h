#pragma once

#include <chrono>
#include <cstdint>
#include <format>
#include <sstream>

namespace domain {

using Time = std::chrono::minutes;
using Date = std::chrono::sys_days;

/**
 * @brief Преобразует строку в дату
 * Строка должна быть задана в формате YYYY-MM-DD
 */
inline Date dateFromString(std::string_view date_as_str) {
    std::istringstream ss{std::string(date_as_str)};
    char separator;
    int year;
    unsigned int month;
    unsigned int day;
    ss >> year >> separator >> month >> separator >> day;
    std::chrono::year_month_day ymd{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
    return std::chrono::sys_days{ymd};
}

inline std::string dateToString(Date date) {
    return std::format("{:%Y-%m-%d}", date);
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

}  // namespace domain
