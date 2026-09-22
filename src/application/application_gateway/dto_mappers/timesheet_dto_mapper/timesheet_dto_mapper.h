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
    GetLeaveTypesResponseDto convert(const domain::LeaveTypeDescriptions& leave_type_descriptions) const override;
};

}  // namespace application