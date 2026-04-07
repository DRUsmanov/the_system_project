#pragma once

#include "domain/value_data/types.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/entities/timesheet/holidays/holiday.h"
#include "domain/entities/timesheet/leave_types/leave_type.h"
#include "domain/entities/timesheet/admin_categorys/admin_category.h"
#include "domain/entities/timesheet/vacations/vacation.h"
#include "domain/entities/timesheet/timesheet.h"

#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <optional>

namespace domain{

using WorkSchedules = std::unordered_map<WorkScheduleId, WorkSchedule, WorkScheduleIdHasher>;
using Holidays = std::unordered_set<Date, DateHasher>;
using ExtraHolidays = std::unordered_set<Date, DateHasher>;
using PreHolidays = std::unordered_set<Date, DateHasher>;
using Vacations = std::unordered_map<EmployeeId, std::vector<Vacation>, EmployeeIdHasher>;

class TimeSheetRepositoryInterface{
public:
    virtual ~TimeSheetRepositoryInterface() = default;

    virtual WorkSchedule DownloadWorkScheduleById(WorkScheduleId id) const = 0;
    virtual PreHolidays DownloadPreHolidaysByYear(std::chrono::year year) const = 0;
    virtual Holidays DownloadHolidaysByYear(std::chrono::year year) const = 0;
    virtual ExtraHolidays DownloadExtraHolidaysByYear(std::chrono::year year) const = 0;
    virtual Vacations DownloadVacationsByShopAndYear(const Shop& shop, std::chrono::year year) const = 0;
    virtual Vacations DownloadVacationsByEmployeeId(EmployeeId employee_id) const = 0;
    virtual AdminCategoryId DownloadSystemAdministratorId() const = 0;
    virtual std::optional<Timesheet> DownloadTimesheet(domain::DepartmentId department_id
                                    , domain::AdminCategoryId admin_category_id
                                    , std::chrono::year_month year_month) const = 0;

    virtual bool UploadTimesheet(const domain::Timesheet& timesheet) = 0;
};

} // namespace domain

