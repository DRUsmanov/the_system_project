#include "application_gateway/dto_mappers/timesheet_dto_mapper/timesheet_dto_mapper.h"

using namespace application;

GetWorkSchedulesResponseDto TimesheetDtoMapper::convert(const domain::WorkSchedules& work_schedules) const {
    GetWorkSchedulesResponseDto get_work_schedule_response_dto;
    for (const auto& [work_schedule_id, work_schedule] : work_schedules) {
        get_work_schedule_response_dto.work_schedules.push_back({*work_schedule_id, work_schedule.getDescription()});
    }
    return get_work_schedule_response_dto;
}

EmployeeInfoDto makeEmployeeInfoDto(const domain::EmployeeId& employee_id, const domain::Employees& employees) {
    EmployeeInfoDto employee_info_dto;
    const auto& employee = employees.at(employee_id);
    employee_info_dto.last_name = employee.last_name;
    employee_info_dto.first_name = employee.first_name;
    employee_info_dto.patronymic = employee.patronymic;
    employee_info_dto.employee_number = employee.employee_number;

    return employee_info_dto;
}

EmployeeDayDataDto makeEmployeeDayDataDto(const domain::Timesheet::DayData& employee_day_data) {
    EmployeeDayDataDto employee_day_data_dto;

    if (employee_day_data.work_time.has_value()) {
        employee_day_data_dto.work_time = domain::timeToString(employee_day_data.work_time.value());
    }

    if (employee_day_data.night_work_time.has_value()) {
        employee_day_data_dto.night_work_time = domain::timeToString(employee_day_data.night_work_time.value());
    }

    if (employee_day_data.leave_type.has_value()) {
        employee_day_data_dto.leave_type_id = static_cast<uint64_t>(employee_day_data.leave_type.value());
    }

    if (employee_day_data.comment.has_value()) {
        employee_day_data_dto.comment = employee_day_data.comment.value();
    }

    employee_day_data_dto.staff_position_id = *employee_day_data.staff_position_id;
    employee_day_data_dto.work_schedule_id = *employee_day_data.work_schedule_id;

    return employee_day_data_dto;
}

std::pair<domain::DepartmentId, domain::Date> TimesheetDtoMapper::convert(
    const GetDepartmentTimesheetRequestDto get_department_timesheet_request_dto) const {
    auto department_id = domain::DepartmentId{get_department_timesheet_request_dto.department_id};
    auto year = std::chrono::year{get_department_timesheet_request_dto.year};
    auto month = std::chrono::month{get_department_timesheet_request_dto.month};
    domain::Date date{year / month / 1};

    return {department_id, date};
}

GetDepartmentTimesheetResponseDto TimesheetDtoMapper::convert(const domain::Timesheet& department_timesheet) const {
    GetDepartmentTimesheetResponseDto get_department_timesheet_response_dto;
    auto& employees_day_data_dto = get_department_timesheet_response_dto.employees_day_data_dto;

    for (auto it = department_timesheet.begin(); it != department_timesheet.end(); ++it) {
        const auto& employee_id = it->first;
        const auto& days_data = it->second;

        for (const auto& [date, day_data] : days_data) {
            auto date_as_string = domain::dateToString(date);
            auto employee_day_data_dto = makeEmployeeDayDataDto(day_data);
            employees_day_data_dto[*employee_id].insert({date_as_string, employee_day_data_dto});
        }
    }

    return get_department_timesheet_response_dto;
}

GetLeaveTypesResponseDto application::TimesheetDtoMapper::convert(
    const domain::LeaveTypeDescriptions& leave_type_descriptions) const {
    GetLeaveTypesResponseDto get_leave_types_response_dto;
    for (const auto& [leave_type, leave_type_description] : leave_type_descriptions) {
        get_leave_types_response_dto.leave_type_desriptions[static_cast<uint64_t>(leave_type)] = leave_type_description;
    }
    return get_leave_types_response_dto;
}
