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

    virtual std::optional<WorkSchedule> downloadWorkScheduleById(const WorkScheduleId& work_schedule_id) const = 0;
    virtual std::optional<WorkSchedules> downloadWorkSchedules() const = 0;
    virtual std::optional<PreHolidays> downloadPreHolidaysByYear(std::chrono::year year) const = 0;
    virtual std::optional<Holidays> downloadHolidaysByYear(std::chrono::year year) const = 0;
    virtual std::optional<ExtraHolidays> downloadExtraHolidaysByYear(std::chrono::year year) const = 0;
    virtual std::optional<EmployeeVacations> downloadVacationsByYear(std::chrono::year year) const = 0;
    virtual std::optional<EmployeeVacations> downloadVacationsByEmployeeId(const EmployeeId& employee_id) const = 0;
    virtual std::optional<EmployeeVacations> downloadVacationsByEmployeeIdAndYear(const EmployeeId& employee_id,
                                                                                  std::chrono::year year) const = 0;
    virtual std::optional<AdminCategoryId> downloadSystemAdministratorId() const = 0;
    virtual std::optional<Timesheet> downloadDepartmentTimesheet(const DepartmentId& department_id,
                                                                 const AdminCategoryId& admin_category_id,
                                                                 std::chrono::year_month year_month) const = 0;
    virtual std::optional<Timesheet> downloadEmployeeTimesheetBetweenDate(const EmployeeId& employee_id,
                                                                          const AdminCategoryId& admin_category_id,
                                                                          const Date& start_date,
                                                                          const Date& end_date) = 0;
    virtual std::optional<Timesheet> downloadEmployeeExtendedVacationsTimesheet(
        const EmployeeId& employee_id,
        const AdminCategoryId& admin_category_id,
        const Date& start_date) = 0;

    virtual std::optional<Date> downloadMaxDate() const = 0;
    virtual bool deleteEmployeeTimesheetFromDate(const domain::EmployeeId& employee_id, const domain::Date& date) = 0;
    virtual bool uploadTimesheet(const Timesheet& timesheet,
                                 const AdminCategoryId& admin_category_id,
                                 std::optional<EmployeeId> admin_employee_id = std::nullopt) = 0;
    virtual bool updateTimesheet(const Timesheet& timesheet,
                                 const AdminCategoryId& admin_category_id,
                                 const EmployeeId& admin_employee_id) = 0;
};

}  // namespace domain
