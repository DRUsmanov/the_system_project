#pragma once

#include <string>
#include <chrono>

namespace application {

struct EmployeeIdDto {
    int employee_id;
};

struct EmployeeDto {
    std::string last_name;
    std::string first_name;
    std::optional<std::string> patronymic;
    std::chrono::sys_days birth_date;
    std::chrono::sys_days employment_date;
    unsigned int employee_number;
};

} // namespace application