#include "application_gateway/dto_mappers/timesheet_dto_mapper/timesheet_dto_mapper.h"

using namespace application;

GetWorkSchedulesResponseDto TimesheetDtoMapper::convert(const domain::WorkSchedules& work_schedules) const {
    GetWorkSchedulesResponseDto get_work_schedule_response_dto;
    for (const auto& work_schedule : work_schedules) {
        get_work_schedule_response_dto.work_schedules.push_back(
            {*work_schedule.getId(), work_schedule.getDescription()});
    }
    return get_work_schedule_response_dto;
}