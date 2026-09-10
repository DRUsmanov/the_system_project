#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace application {

// ======================================================================
// ADD EMPLOYEE
// ======================================================================

struct AddEmployeeRequestDto {
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string birth_date;
    std::string employment_date;
    uint64_t employee_number;
    uint64_t department_id;
    uint64_t staff_position_id;
    uint64_t work_schedule_id;
};

struct AddEmployeeResponseDto {
    uint64_t employee_id;
};

// ======================================================================
// REMOVE EMPLOYEE
// ======================================================================

struct RemoveEmployeeRequestDto {
    uint64_t employee_id;
};

struct RemoveEmployeeResponseDto {
    bool is_removed = false;
};

// ======================================================================
// GET EMPLOYEE
// ======================================================================

// struct GetEmployeeRequestDto {
//     uint64_t employee_id;
// };

// struct GetEmployeeResponseDto {
//     std::string last_name;
//     std::string first_name;
//     std::optional<std::string> patronymic;
//     std::chrono::sys_days birth_date;
//     std::chrono::sys_days employment_date;
//     uint64_t employee_number;
// };

}  // namespace application
