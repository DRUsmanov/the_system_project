#pragma once

#include "domain/value_data/types.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/entities/timesheet/holidays/holiday.h"
#include "domain/entities/timesheet/leave_types/leave_type.h"
#include "domain/entities/timesheet/administrators/administrator.h"
#include "domain/entities/timesheet/vacations/vacation.h"

#include <unordered_map>
#include <unordered_set>
#include <chrono>

namespace domain{

using WorkSchedules = std::unordered_map<WorkScheduleId, WorkSchedule, WorkScheduleIdHasher>;
using Holidays = std::unordered_set<Date, DateHasher>;
using ExtraHolidays = std::unordered_set<Date, DateHasher>;
using PreHolidays = std::unordered_set<Date, DateHasher>;
using Vacations = std::unordered_set<Vacation, VacationHasher>;

using LeaveTypes = std::unordered_map<LeaveTypeId, LeaveType, LeaveTypeIdHasher>;

class TimeSheetRepositoryInterface{
public:
    virtual ~TimeSheetRepositoryInterface() = default;

    virtual WorkSchedule LoadWorkScheduleById(WorkScheduleId id) const = 0;
    virtual Holidays LoadHolidaysByYear(std::chrono::year year) const = 0;
    virtual ExtraHolidays LoadExtraHolidaysByYear(std::chrono::year year) const = 0;
    virtual PreHolidays LoadPreHolidaysByYear(std::chrono::year year) const = 0;
    virtual Vacations LoadVacationsByEmployeeId(EmployeeId employee_id) const = 0;
    virtual AdministratorId LoadSystemAdministratorId() const = 0;
};

} // namespace domain

