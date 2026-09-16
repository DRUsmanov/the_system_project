#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <unordered_map>

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
    std::string removing_date;
    uint64_t employee_id;
};

// ======================================================================
// GET DEPARTMENTS
// ======================================================================

struct GetDepartmentsResponseDto {
    std::unordered_map<uint64_t, std::string> departmens;
};

// ======================================================================
// GET STAFF POSITONS
// ======================================================================

struct GetStaffPositionsResponseDto {
    std::unordered_map<uint64_t, std::string> staff_positions;
};

// ======================================================================
// GET DEPARTMENTS STAFF
// ======================================================================

struct GetDepartmentStaffRequestDto {
    uint64_t department_id;
};

struct GetDepartmentStaffResponseDto {
    struct Data {
        uint64_t employee_id;
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
    std::vector<Data> data;
};

// ======================================================================
// UPDATE EMPLOYE
// ======================================================================

struct UpdateEmployeeRequestDto {
    std::optional<std::string> assignment_changing_date;
    uint64_t employee_id;
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

}  // namespace application
