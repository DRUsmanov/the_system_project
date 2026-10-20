#pragma once

#include "application_gateway/dto_mappers/timesheet_dto_mapper/timesheet_dto_mapper_interface.h"

namespace application {

class TimesheetDtoMapper : public TimesheetDtoMapperInterface {
public:
    // GET WORKSCHEDULE
    GetWorkSchedulesResponseDto convert(const domain::WorkSchedules& work_schedules) const override;

    // GET DEPARTMENT TIMESHEET
    std::pair<domain::DepartmentId, domain::Date> convert(
        const GetDepartmentTimesheetRequestDto get_department_timesheet_request_dto) const override;

    GetDepartmentTimesheetResponseDto convert(const domain::Timesheet& department_timesheet) const override;

    // GET LEAVE TYPES
    GetLeaveTypesResponseDto convert(const domain::LeaveTypeDescriptions& leave_type_descriptions) const override;

    // UPDATE EMPLOYEE TIMESHEET DAYS DATA
    std::tuple<domain::EmployeeId, domain::Date, domain::Date, domain::Timesheet::DayData> convert(
        const UpdateEmployeeTimesheetDaysDataRequestDto& update_employee_timesheet_days_data_request_dto)
        const override;

    // SET EMPLOYEE LEAVE TYPE IN TIMESHEET
    std::tuple<domain::EmployeeId, domain::Date, domain::Date, domain::LeaveType> convert(
        const SetEmployeeLeaveTypeInTimesheetRequestDto& set_employee_leave_type_in_timesheet_request_dto)
        const override;

    // CHANGE EMPLOYEE ASSIGNMENT IN TIMESHEET
    std::tuple<domain::EmployeeId, domain::Date, domain::Date, domain::EmployeeAssignment> convert(
        const ChangeEmployeeAssignmentInTimesheetRequestDto& change_employee_assignment_in_timesheet_request_dto)
        const override;
};

}  // namespace application