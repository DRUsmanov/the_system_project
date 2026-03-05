#pragma once

#include "../../entities/work_shedule.h"


#include <unordered_map>
#include <vector>
#include <optional>

namespace domain{

namespace table{
    struct Departments{};
    struct StaffPositions{};
    struct WorkSchedules{};
    struct StaffingAssignments{};
    struct Employees{};
    struct Timesheet{};
    struct OvertimeWork{};
    struct WeekendWork{};
    struct LeaveTypes{};
    struct Holidays{};
    struct ExtraHolidaysDays{};
    struct PreHolidaysDay{};
}

using Schedule = std::vector<WorkSheduleDayData>;
using SchedulesTable = std::unordered_map<WorkScheduleId, Schedule, WorkScheduleIdHasher>;

using Vacations = std::vector<VacationData>;




class TimeSheetRepositoryInterface{
public:
    virtual ~TimeSheetRepositoryInterface() = default;

    virtual SchedulesTable GetShedulesTable() = 0;
    
};

} // namespace domain

