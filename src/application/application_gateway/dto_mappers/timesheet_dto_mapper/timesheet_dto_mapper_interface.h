#pragma once

#include "application_gateway/dto/timesheet_dto.h"
#include "entities/timesheet/timesheet.h"

namespace application {

class TimesheetDtoMapperInterface {
public:
    virtual ~TimesheetDtoMapperInterface() = default;

    // GET WORKSCHEDULE
    virtual GetWorkSchedulesResponseDto convert(const domain::WorkSchedules& work_schedules) const = 0;
};

}  // namespace application