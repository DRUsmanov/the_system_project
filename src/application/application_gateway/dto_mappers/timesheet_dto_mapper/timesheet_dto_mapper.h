#pragma once

#include "application_gateway/dto_mappers/timesheet_dto_mapper/timesheet_dto_mapper_interface.h"

namespace application {

class TimesheetDtoMapper : public TimesheetDtoMapperInterface {
public:
    // GET WORKSCHEDULE
    GetWorkSchedulesResponseDto convert(const domain::WorkSchedules& work_schedules) const override;
};

}  // namespace application