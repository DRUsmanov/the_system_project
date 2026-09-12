#pragma once

#include <chrono>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "entities/timesheet/admin_categorys/admin_category.h"
#include "entities/timesheet/holidays/holiday.h"
#include "entities/timesheet/leave_types/leave_type.h"
#include "entities/timesheet/timesheet.h"
#include "entities/timesheet/vacations/vacation.h"
#include "entities/timesheet/work_schedules/work_schedule.h"
#include "value_data/types.h"

namespace domain {

using EmployeeVacations = std::unordered_map<EmployeeId, Vacations, EmployeeIdHasher>;

class TimeSheetRepositoryInterface {
public:
    virtual ~TimeSheetRepositoryInterface() = default;

    virtual std::optional<WorkSchedule> downloadWorkScheduleById(WorkScheduleId work_schedule_id) const = 0;
    virtual std::optional<WorkSchedules> downloadWorkSchedules() const = 0;
    virtual std::optional<PreHolidays> downloadPreHolidaysByYear(std::chrono::year year) const = 0;
    virtual std::optional<Holidays> downloadHolidaysByYear(std::chrono::year year) const = 0;
    virtual std::optional<ExtraHolidays> downloadExtraHolidaysByYear(std::chrono::year year) const = 0;
    virtual std::optional<EmployeeVacations> downloadVacationsByYear(std::chrono::year year) const = 0;
    virtual std::optional<EmployeeVacations> downloadVacationsByEmployeeId(EmployeeId employee_id) const = 0;
    virtual std::optional<EmployeeVacations> downloadVacationsByEmployeeIdAndYear(EmployeeId employee_id,
                                                                                  std::chrono::year year) const = 0;
    virtual std::optional<AdminCategoryId> downloadSystemAdministratorId() const = 0;
    virtual std::optional<Timesheet> downloadDepartmentTimesheet(DepartmentId department_id,
                                                                 AdminCategoryId admin_category_id,
                                                                 std::chrono::year_month year_month) const = 0;

    virtual bool uploadTimesheet(const Timesheet& timesheet,
                                 AdminCategoryId admin_category_id,
                                 std::optional<EmployeeId> admin_employee_id = std::nullopt) = 0;
};

}  // namespace domain
