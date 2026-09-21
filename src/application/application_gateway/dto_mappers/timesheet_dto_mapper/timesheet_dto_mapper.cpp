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

EmployeeDayDataDto makeEmployeeDayDataDto(const domain::Timesheet::DayData& employee_day_data,
                                          const domain::StaffPositions& staff_positions,
                                          const domain::WorkSchedules& work_schedules,
                                          const domain::LeaveTypeDescriptions& leave_type_descriptions) {
    EmployeeDayDataDto employee_day_data_dto;

    if (employee_day_data.work_time.has_value()) {
        employee_day_data_dto.work_time = domain::timeToString(employee_day_data.work_time.value());
    }

    if (employee_day_data.night_work_time.has_value()) {
        employee_day_data_dto.night_work_time = domain::timeToString(employee_day_data.night_work_time.value());
    }

    if (employee_day_data.leave_type.has_value()) {
        employee_day_data_dto.leave_type = leave_type_descriptions.at(employee_day_data.leave_type.value());
    }

    if (employee_day_data.comment.has_value()) {
        employee_day_data_dto.comment = employee_day_data.comment.value();
    }

    employee_day_data_dto.staff_position_description =
        staff_positions.at(employee_day_data.staff_position_id).description;
    employee_day_data_dto.work_schedule_description =
        work_schedules.at(employee_day_data.work_schedule_id).getDescription();

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

GetDepartmentTimesheetResponseDto TimesheetDtoMapper::convert(
    const domain::Timesheet& department_timesheet,
    const domain::Employees& employees,
    const domain::WorkSchedules& work_schedules,
    const domain::StaffPositions& staff_positions,
    const domain::LeaveTypeDescriptions& leave_type_descriptions) const {
    GetDepartmentTimesheetResponseDto get_department_timesheet_response_dto;
    auto& employees_info_dto = get_department_timesheet_response_dto.employees_info_dto;
    auto& employees_day_data_dto = get_department_timesheet_response_dto.employees_day_data_dto;

    for (auto it = department_timesheet.begin(); it != department_timesheet.end(); ++it) {
        const auto& employee_id = it->first;
        const auto& days_data = it->second;

        auto employee_info_dto = makeEmployeeInfoDto(employee_id, employees);

        employees_info_dto.insert({*employee_id, employee_info_dto});

        for (const auto& [date, day_data] : days_data) {
            auto date_as_string = domain::dateToString(date);
            auto employee_day_data_dto =
                makeEmployeeDayDataDto(day_data, staff_positions, work_schedules, leave_type_descriptions);
            employees_day_data_dto[*employee_id].insert({date_as_string, employee_day_data_dto});
        }
    }

    return get_department_timesheet_response_dto;
}
