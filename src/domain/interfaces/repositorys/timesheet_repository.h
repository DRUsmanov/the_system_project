#pragma once

#include "domain/value_data/types.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/entities/timesheet/holidays/holiday.h"
#include "domain/entities/timesheet/leave_types/leave_type.h"
#include "domain/entities/timesheet/administrators/administrator.h"
#include "domain/entities/timesheet/vacations/vacation.h"

#include <unordered_map>
#include <unordered_set>

namespace domain{

using WorkSchedules = std::unordered_map<WorkScheduleId, WorkSchedule, WorkScheduleIdHasher>;
using Holidays = std::unordered_set<Date>;
using ExtraHolidays = std::unordered_set<Date>;
using PreHolidays = std::unordered_set<Date>;
using LeaveTypes = std::unordered_map<LeaveTypeId, LeaveType, LeaveTypeIdHasher>;

class TimeSheetRepositoryInterface{
public:
    virtual ~TimeSheetRepositoryInterface() = default;

    virtual WorkSchedules GetWorkSchedules() const = 0;
    virtual Holidays GetHolidays(std::chrono::year year) const = 0;
    virtual ExtraHolidays GetExtraHolidays(std::chrono::year year) const = 0;
    virtual PreHolidays GetPreHolidays(std::chrono::year year) const = 0;
    virtual LeaveTypes GetLeaveTypes() const = 0;
    virtual AdministratorId GetSystemAdministratorId() const = 0;
};

} // namespace domain

