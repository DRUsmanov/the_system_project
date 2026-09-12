#include "services/timesheet_service/timesheet_service.h"

#include <chrono>
#include <exception>
#include <unordered_map>
#include <vector>

#include "entities/timesheet/leave_types/leave_type.h"
#include "entities/timesheet/timesheet.h"
#include "entities/timesheet/work_schedules/work_schedule.h"
#include "logger.h"
#include "value_data/types.h"

using namespace domain;

std::optional<Timesheet> TimesheetService::getDepartmentTimesheet(DepartmentId department_id,
                                                                  AdminCategoryId admin_category_id,
                                                                  std::chrono::year_month year_month) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return timesheet_repository_->downloadDepartmentTimesheet(department_id, admin_category_id, year_month);
}

bool TimesheetService::generateEmployeeVacationsInTimesheet(Timesheet& timesheet,
                                                            const TimesheetGenerationContext& generation_context) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    if (!generation_context.employee_vacations.has_value()) {
        return false;
    }
    auto it = generation_context.employee_vacations.value().find(generation_context.employee_id);
    if (it == generation_context.employee_vacations.value().end()) {
        return false;
    }

    for (const auto& vacation : it->second) {
        if (vacation.isVacationDay(generation_context.date)) {
            auto vacation_day_data = Timesheet::DayData::createNonWorkingDayData(LeaveType::VACATION,
                                                                                 generation_context.department_id,
                                                                                 generation_context.staff_position_id,
                                                                                 generation_context.work_schedule_id);
            timesheet.addEmployeeDayData(generation_context.employee_id,
                                         generation_context.date,
                                         generation_context.admin_category_id,
                                         vacation_day_data);
            return true;
        }
    }

    return false;
}

bool TimesheetService::generateHolidaysAndPreHolidaysInTimesheet(Timesheet& timesheet,
                                                                 const TimesheetGenerationContext& generation_context) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    const auto& work_schedule_day_data = generation_context.work_schedule.getDayDataByDate(generation_context.date);

    if (generation_context.work_schedule.isWorksOnHolidays()) {
        return false;
    }

    if (generation_context.pre_holidays.has_value() &&
        generation_context.pre_holidays.value().contains(generation_context.date)) {
        auto pre_holidays_day_data = Timesheet::DayData::createWorkingDayData(work_schedule_day_data,
                                                                              generation_context.department_id,
                                                                              generation_context.staff_position_id,
                                                                              generation_context.work_schedule_id);

        pre_holidays_day_data.work_end.value() -= std::chrono::hours{1};
        pre_holidays_day_data.work_time.value() -= std::chrono::hours{1};

        timesheet.addEmployeeDayData(generation_context.employee_id,
                                     generation_context.date,
                                     generation_context.admin_category_id,
                                     pre_holidays_day_data);
        return true;
    }

    if (generation_context.holidays.has_value() &&
        generation_context.holidays.value().contains(generation_context.date)) {
        // Не добавляем день в табель
        return true;
    }

    if (generation_context.extra_holidays.has_value() &&
        generation_context.extra_holidays.value().contains(generation_context.date)) {
        // Не добавляем день в табель
        return true;
    }

    return false;
}

bool TimesheetService::generateWorkingDayInTimesheet(Timesheet& timesheet,
                                                     const TimesheetGenerationContext& generation_context) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    const auto& work_schedule_day_data = generation_context.work_schedule.getDayDataByDate(generation_context.date);

    if (work_schedule_day_data.isWorkingDay()) {
        auto working_day_data = Timesheet::DayData::createWorkingDayData(work_schedule_day_data,
                                                                         generation_context.department_id,
                                                                         generation_context.staff_position_id,
                                                                         generation_context.work_schedule_id);

        timesheet.addEmployeeDayData(generation_context.employee_id,
                                     generation_context.date,
                                     generation_context.admin_category_id,
                                     working_day_data);
        return true;
    }
    return false;
}

std::chrono::year_month_day TimesheetService::getCurrentDate() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    using namespace std::chrono;
    using namespace std::literals;

    auto now = system_clock::now();
    auto days = floor<std::chrono::days>(now);
    year_month_day ymd{days};
    return ymd;
}

bool TimesheetService::generateTimesheetForShop(const Shop& shop, std::chrono::year year) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    using namespace std::chrono;
    using namespace std::literals;
    using WorkSchedules = std::unordered_map<WorkScheduleId, WorkSchedule, WorkScheduleIdHasher>;

    Timesheet timesheet;
    WorkSchedules work_schedules_cache;

    const auto& employees_assignments = shop.getEmployeeAssignments();

    auto pre_holidays = timesheet_repository_->downloadPreHolidaysByYear(year);
    auto holidays = timesheet_repository_->downloadHolidaysByYear(year);
    auto extra_holidays = timesheet_repository_->downloadExtraHolidaysByYear(year);
    auto employee_vacations = timesheet_repository_->downloadVacationsByYear(year);
    auto system_administrator_id = timesheet_repository_->downloadSystemAdministratorId();

    if (!pre_holidays || !holidays || !extra_holidays || !system_administrator_id || !employee_vacations) {
        return false;
    }

    for (const auto& [employee_id, employee_assignment] : employees_assignments) {
        const auto& work_schedule_id = employee_assignment.work_schedule_id;
        const auto& department_id = employee_assignment.department_id;
        const auto& staff_position_id = employee_assignment.staff_position_id;

        if (!work_schedules_cache.contains(work_schedule_id)) {
            auto work_schedule = timesheet_repository_->downloadWorkScheduleById(work_schedule_id);
            if (!work_schedule) {
                return false;
            }
            work_schedules_cache[work_schedule_id] = *work_schedule;
        }
        const auto& work_schedule = work_schedules_cache[work_schedule_id];

        auto start_date = sys_days{year / January / 1};
        auto end_date = sys_days{year / December / 31};

        for (auto date = start_date; date <= end_date; date += std::chrono::days{1}) {
            TimesheetGenerationContext generation_context{*system_administrator_id,
                                                          date,
                                                          employee_id,
                                                          department_id,
                                                          staff_position_id,
                                                          work_schedule_id,
                                                          work_schedule,
                                                          *pre_holidays,
                                                          *holidays,
                                                          *extra_holidays,
                                                          *employee_vacations};

            if (generateEmployeeVacationsInTimesheet(timesheet, generation_context)) {
                continue;
            }

            if (generateHolidaysAndPreHolidaysInTimesheet(timesheet, generation_context)) {
                continue;
            }

            generateWorkingDayInTimesheet(timesheet, generation_context);
        }
    }

    return timesheet_repository_->uploadTimesheet(timesheet, *system_administrator_id);
}

bool TimesheetService::generateTimesheetForNewEmployee(const Shop::EmployeeAssignment& employee_assignment,
                                                       const Employee& employee) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    using namespace std::chrono;
    using namespace std::literals;

    Timesheet timesheet;

    auto employment_year = std::chrono::year_month_day{employee.employment_date}.year();

    auto pre_holidays = timesheet_repository_->downloadPreHolidaysByYear(employment_year);
    auto holidays = timesheet_repository_->downloadHolidaysByYear(employment_year);
    auto extra_holidays = timesheet_repository_->downloadExtraHolidaysByYear(employment_year);
    auto system_administrator_id = timesheet_repository_->downloadSystemAdministratorId();
    auto work_schedule = timesheet_repository_->downloadWorkScheduleById(employee_assignment.work_schedule_id);
    auto employee_vacations =
        timesheet_repository_->downloadVacationsByEmployeeIdAndYear(employee.employee_id, employment_year);

    if (!system_administrator_id || !work_schedule) {
        return false;
    }

    auto start_date = employee.employment_date;
    auto end_date = employment_year / December / 31;

    for (auto date = start_date; date <= end_date; date += std::chrono::days{1}) {
        TimesheetGenerationContext generation_context{*system_administrator_id,
                                                      date,
                                                      employee.employee_id,
                                                      employee_assignment.department_id,
                                                      employee_assignment.staff_position_id,
                                                      employee_assignment.work_schedule_id,
                                                      *work_schedule,
                                                      pre_holidays,
                                                      holidays,
                                                      extra_holidays,
                                                      employee_vacations};

        if (generateEmployeeVacationsInTimesheet(timesheet, generation_context)) {
            continue;
        }

        if (generateHolidaysAndPreHolidaysInTimesheet(timesheet, generation_context)) {
            continue;
        }

        generateWorkingDayInTimesheet(timesheet, generation_context);
    }

    return timesheet_repository_->uploadTimesheet(timesheet, *system_administrator_id);
}

std::optional<WorkSchedules> TimesheetService::getWorkSchedules() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return timesheet_repository_->downloadWorkSchedules();
}
