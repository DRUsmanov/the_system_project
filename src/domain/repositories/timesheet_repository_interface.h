#pragma once

#include <chrono>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "domain/entities/timesheet/admin_categorys/admin_category.h"
#include "domain/entities/timesheet/holidays/holiday.h"
#include "domain/entities/timesheet/leave_types/leave_type.h"
#include "domain/entities/timesheet/timesheet.h"
#include "domain/entities/timesheet/vacations/vacation.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/value_data/types.h"

namespace domain {

using WorkSchedules = std::unordered_map<WorkScheduleId, WorkSchedule, WorkScheduleIdHasher>;
using Holidays = std::unordered_set<Date, DateHasher>;
using ExtraHolidays = std::unordered_set<Date, DateHasher>;
using PreHolidays = std::unordered_set<Date, DateHasher>;
using Vacations = std::unordered_map<EmployeeId, std::vector<Vacation>, EmployeeIdHasher>;

class TimeSheetRepositoryInterface {
public:
    virtual ~TimeSheetRepositoryInterface() = default;

    virtual WorkSchedule downloadWorkScheduleById(WorkScheduleId id) const = 0;
    virtual PreHolidays downloadPreHolidaysByYear(std::chrono::year year) const = 0;
    virtual Holidays downloadHolidaysByYear(std::chrono::year year) const = 0;
    virtual ExtraHolidays downloadExtraHolidaysByYear(std::chrono::year year) const = 0;
    virtual Vacations downloadVacationsByYear(std::chrono::year year) const = 0;
    virtual Vacations downloadVacationsByEmployeeId(EmployeeId employee_id) const = 0;
    virtual Vacations downloadVacationsByEmployeeIdAndYear(EmployeeId employee_id, std::chrono::year year) const = 0;
    virtual AdminCategoryId downloadSystemAdministratorId() const = 0;
    virtual std::optional<Timesheet> downloadDepartmentTimesheet(DepartmentId department_id,
                                                                 AdminCategoryId admin_category_id,
                                                                 std::chrono::year_month year_month) const = 0;

    virtual bool uploadTimesheet(const Timesheet& timesheet) = 0;
};

}  // namespace domain
