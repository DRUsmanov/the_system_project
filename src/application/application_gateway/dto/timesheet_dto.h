#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace application {

// ======================================================================
// GET WORK SCHEDULE
// ======================================================================

struct GetWorkSchedulesResponseDto {
    std::vector<std::pair<uint64_t, std::string>> work_schedules;
};

// ======================================================================
// GET DEPARTMENT TIMESHEET
// ======================================================================

struct GetDepartmentTimesheetRequestDto {
    uint64_t department_id;
    int year;
    uint month;
};

struct EmployeeInfoDto {
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    uint64_t employee_number;
};

struct EmployeeDayDataDto {
    std::optional<std::string> work_time;
    std::optional<std::string> night_work_time;
    std::optional<std::string> leave_type;
    std::optional<std::string> comment;
    std::string staff_position_description;
    std::string work_schedule_description;
};

struct GetDepartmentTimesheetResponseDto {
    std::unordered_map<uint64_t, EmployeeInfoDto> employees_info_dto;
    std::unordered_map<uint64_t, std::unordered_map<std::string, EmployeeDayDataDto>> employees_day_data_dto;
};

}  // namespace application
