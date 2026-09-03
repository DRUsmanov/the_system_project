#pragma once

#include "repositories/timesheet_repository_interface.h"
#include "uow_impl/uow_impl.h"

namespace infrastructure {

class TimesheetRepository : public domain::TimeSheetRepositoryInterface {
public:
    TimesheetRepository(std::shared_ptr<Uow> uow) : uow_{uow} {}

    domain::WorkSchedule downloadWorkScheduleById(domain::WorkScheduleId id) const override;
    domain::PreHolidays downloadPreHolidaysByYear(std::chrono::year year) const override;
    domain::Holidays downloadHolidaysByYear(std::chrono::year year) const override;
    domain::ExtraHolidays downloadExtraHolidaysByYear(std::chrono::year year) const override;
    domain::Vacations downloadVacationsByYear(std::chrono::year year) const override;
    domain::Vacations downloadVacationsByEmployeeId(domain::EmployeeId employee_id) const override;
    domain::Vacations downloadVacationsByEmployeeIdAndYear(domain::EmployeeId employee_id,
                                                           std::chrono::year year) const override;
    domain::AdminCategoryId downloadSystemAdministratorId() const override;
    std::optional<domain::Timesheet> downloadDepartmentTimesheet(domain::DepartmentId department_id,
                                                                 domain::AdminCategoryId admin_category_id,
                                                                 std::chrono::year_month year_month) const override;

    bool uploadTimesheet(const domain::Timesheet& timesheet) override;

private:
    std::shared_ptr<Uow> uow_;
};

}  // namespace infrastructure
