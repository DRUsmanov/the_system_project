#pragma once

#include "repositories/timesheet_repository_interface.h"
#include "uow_impl/uow_impl.h"

namespace infrastructure {

class TimesheetRepository : public domain::TimeSheetRepositoryInterface {
public:
    TimesheetRepository(std::shared_ptr<Uow> uow) : uow_{uow} {}

    std::optional<domain::WorkSchedule> downloadWorkScheduleById(
        domain::WorkScheduleId work_schedule_id) const override;
    std::optional<domain::WorkSchedules> downloadWorkSchedules() const override;
    std::optional<domain::PreHolidays> downloadPreHolidaysByYear(std::chrono::year year) const override;
    std::optional<domain::Holidays> downloadHolidaysByYear(std::chrono::year year) const override;
    std::optional<domain::ExtraHolidays> downloadExtraHolidaysByYear(std::chrono::year year) const override;
    std::optional<domain::EmployeeVacations> downloadVacationsByYear(std::chrono::year year) const override;
    std::optional<domain::EmployeeVacations> downloadVacationsByEmployeeId(
        domain::EmployeeId employee_id) const override;
    std::optional<domain::EmployeeVacations> downloadVacationsByEmployeeIdAndYear(
        domain::EmployeeId employee_id,
        std::chrono::year year) const override;
    std::optional<domain::AdminCategoryId> downloadSystemAdministratorId() const override;
    std::optional<domain::Timesheet> downloadDepartmentTimesheet(domain::DepartmentId department_id,
                                                                 domain::AdminCategoryId admin_category_id,
                                                                 std::chrono::year_month year_month) const override;

    bool uploadTimesheet(const domain::Timesheet& timesheet,
                         domain::AdminCategoryId admin_category_id,
                         std::optional<domain::EmployeeId> admin_employee_id = std::nullopt) override;

private:
    std::shared_ptr<Uow> uow_;
};

}  // namespace infrastructure
