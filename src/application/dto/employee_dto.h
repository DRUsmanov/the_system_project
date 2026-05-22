#pragma once

#include <string>
#include <chrono>
#include <string>

namespace application {

struct AddEmployeeInputDto {
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string birth_date;
    std::string employment_date;
    int employee_number;
    int department_id;
    int staff_position_id;
    int work_schedule_id;
};

struct EmployeeIdInputDto {
    int employee_id;
};

struct EmployeeOutputDto {
    std::string last_name;
    std::string first_name;
    std::optional<std::string> patronymic;
    std::chrono::sys_days birth_date;
    std::chrono::sys_days employment_date;
    unsigned int employee_number;
};

} // namespace application