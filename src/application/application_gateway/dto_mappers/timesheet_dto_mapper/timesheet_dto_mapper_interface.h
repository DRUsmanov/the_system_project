#pragma once

#include "application_gateway/dto/timesheet_dto.h"
#include "entities/timesheet/timesheet.h"

namespace application {

class TimesheetDtoMapperInterface {
public:
    virtual ~TimesheetDtoMapperInterface() = default;

    // GET WORKSCHEDULE
    virtual GetWorkSchedulesResponseDto convert(const domain::WorkSchedules& work_schedules) const = 0;

    // GET DEPARTMENT TIMESHEET
    virtual std::pair<domain::DepartmentId, domain::Date> convert(
        const GetDepartmentTimesheetRequestDto get_department_timesheet_request_dto) const = 0;

    virtual GetDepartmentTimesheetResponseDto convert(const domain::Timesheet& department_timesheet) const = 0;

    // GET LEAVE TYPES
    virtual GetLeaveTypesResponseDto convert(const domain::LeaveTypeDescriptions& leave_type_descriptions) const = 0;
};

}  // namespace application