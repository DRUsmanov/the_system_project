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
    std::optional<std::string> work_start;
    std::optional<std::string> work_end;
    std::optional<std::string> work_time;
    std::optional<std::string> night_work_start;
    std::optional<std::string> night_work_end;
    std::optional<std::string> night_work_time;
    std::optional<std::string> rest_start;
    std::optional<std::string> rest_end;
    std::optional<uint64_t> leave_type_id;
    std::optional<std::string> comment;
    uint64_t staff_position_id;
    uint64_t work_schedule_id;
};

struct GetDepartmentTimesheetResponseDto {
    std::unordered_map<uint64_t, std::unordered_map<std::string, EmployeeDayDataDto>> employees_day_data_dto;
};

// ======================================================================
// GET LEAVE TYPES
// ======================================================================

struct GetLeaveTypesResponseDto {
    std::unordered_map<uint64_t, std::string> leave_type_desriptions;
};

// ======================================================================
// UPDATE EMPLOYEE TIMESHHET
// ======================================================================

struct UpdateEmployeeTimesheetDaysDataRequestDto {
    uint64_t employee_id;
    std::string start_date;
    std::string end_date;
    std::optional<std::string> work_start;
    std::optional<std::string> work_end;
    std::optional<std::string> work_time;
    std::optional<std::string> night_work_start;
    std::optional<std::string> night_work_end;
    std::optional<std::string> night_work_time;
    std::optional<std::string> rest_start;
    std::optional<std::string> rest_end;
    std::optional<std::string> comment;
};

// ======================================================================
// SET EMPLOYEE LEAVE TYPE IN TIMESHHET
// ======================================================================

struct SetEmployeeLeaveTypeInTimesheetRequestDto {
    uint64_t employee_id;
    std::string start_date;
    std::string end_date;
    uint64_t leave_type;
};

// ======================================================================
// CHANGE EMPLOYEE ASSIGNMENT IN TIMESHHET
// ======================================================================

struct ChangeEmployeeAssignmentInTimesheetRequestDto {
    uint64_t employee_id;
    std::string start_date;
    std::string end_date;
    uint64_t department_id;
    uint64_t staff_position_id;
    uint64_t work_schedule_id;
};

}  // namespace application
