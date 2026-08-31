#include "timesheet_repository.h"

using namespace infrastructure;

domain::WorkSchedule TimesheetRepository::downloadWorkScheduleById(domain::WorkScheduleId id) const {
    return domain::WorkSchedule();
}

domain::PreHolidays TimesheetRepository::downloadPreHolidaysByYear(std::chrono::year year) const {
    return domain::PreHolidays();
}

domain::Holidays TimesheetRepository::downloadHolidaysByYear(std::chrono::year year) const {
    return domain::Holidays();
}

domain::ExtraHolidays TimesheetRepository::downloadExtraHolidaysByYear(std::chrono::year year) const {
    return domain::ExtraHolidays();
}

domain::Vacations TimesheetRepository::downloadVacationsByYear(std::chrono::year year) const {
    return domain::Vacations();
}

domain::Vacations TimesheetRepository::downloadVacationsByEmployeeId(domain::EmployeeId employee_id) const {
    return domain::Vacations();
}

domain::Vacations TimesheetRepository::downloadVacationsByEmployeeIdAndYear(domain::EmployeeId employee_id,
                                                                            std::chrono::year year) const {
    return domain::Vacations();
}

std::optional<domain::Timesheet> TimesheetRepository::downloadDepartmentTimesheet(
    domain::DepartmentId department_id,
    domain::AdminCategoryId admin_category_id,
    std::chrono::year_month year_month) const {
    return std::optional<domain::Timesheet>();
}

bool TimesheetRepository::uploadTimesheet(const domain::Timesheet& timesheet) {
    return false;
}
