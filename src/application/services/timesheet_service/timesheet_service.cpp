#include "services/timesheet_service/timesheet_service.h"

#include <chrono>
#include <exception>
#include <unordered_map>
#include <vector>

#include "entities/timesheet/leave_types/leave_type.h"
#include "entities/timesheet/timesheet.h"
#include "entities/timesheet/work_schedules/work_schedule.h"
#include "value_data/types.h"

using namespace application;

std::optional<domain::Timesheet> TimesheetService::getDepartmentTimesheet(domain::DepartmentId department_id,
                                                                          domain::AdminCategoryId admin_category_id,
                                                                          std::chrono::year_month year_month) const {
    return timesheet_repository_->downloadDepartmentTimesheet(department_id, admin_category_id, year_month);
}

bool TimesheetService::generateEmployeeVacationsInTimesheet(domain::Timesheet& timesheet,
                                                            const TimesheetGenerationContext& generation_context) {
    auto it = generation_context.vacations.find(generation_context.employee_id);
    if (it == generation_context.vacations.end()) {
        return false;
    }

    for (const auto& vacation : it->second) {
        if (vacation.isVacationDay(generation_context.date)) {
            auto vacation_day_data =
                domain::Timesheet::DayData::createNonWorkingDayData(domain::LeaveType::VACATION,
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

bool TimesheetService::generateHolidaysInTimesheet(domain::Timesheet& timesheet,
                                                   const TimesheetGenerationContext& generation_context) {
    const auto& work_schedule_day_data = generation_context.work_schedule.getDayDataByDate(generation_context.date);

    if (!generation_context.work_schedule.isWorksOnHolidays()) {
        if (generation_context.pre_holidays.contains(generation_context.date)) {
            auto pre_holidays_day_data =
                domain::Timesheet::DayData::createWorkingDayData(work_schedule_day_data,
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
        } else if (generation_context.holidays.contains(generation_context.date)) {
            // Не добавляем день в табель
            return true;
        } else if (generation_context.extra_holidays.contains(generation_context.date)) {
            // Не добавляем день в табель
            return true;
        }
    }
    return false;
}

bool TimesheetService::generateWorkingDayInTimesheet(domain::Timesheet& timesheet,
                                                     const TimesheetGenerationContext& generation_context) {
    const auto& work_schedule_day_data = generation_context.work_schedule.getDayDataByDate(generation_context.date);

    if (work_schedule_day_data.isWorkingDay()) {
        auto working_day_data = domain::Timesheet::DayData::createWorkingDayData(work_schedule_day_data,
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

std::chrono::year_month_day application::TimesheetService::getCurrentData() const {
    using namespace std::chrono;
    using namespace std::literals;

    auto now = system_clock::now();
    auto days = floor<std::chrono::days>(now);
    year_month_day ymd{days};
    return ymd;
}

bool TimesheetService::generateTimesheetForShop(const domain::Shop& shop, std::chrono::year year) {
    using namespace std::chrono;
    using namespace std::literals;
    using WorkSchedules =
        std::unordered_map<domain::WorkScheduleId, domain::WorkSchedule, domain::WorkScheduleIdHasher>;

    domain::Timesheet timesheet;
    WorkSchedules work_schedules_cache;

    const auto& employees_assignments = shop.getEmployeeAssignments();

    auto pre_holidays = timesheet_repository_->downloadPreHolidaysByYear(year);
    auto holidays = timesheet_repository_->downloadHolidaysByYear(year);
    auto extra_holidays = timesheet_repository_->downloadExtraHolidaysByYear(year);
    auto vacations = timesheet_repository_->downloadVacationsByYear(year);
    auto system_administrator_id = timesheet_repository_->downloadSystemAdministratorId();

    for (const auto& [employee_id, employee_assignment] : employees_assignments) {
        const auto& work_schedule_id = employee_assignment.work_schedule_id;
        const auto& department_id = employee_assignment.department_id;
        const auto& staff_position_id = employee_assignment.staff_position_id;

        if (!work_schedules_cache.contains(work_schedule_id)) {
            work_schedules_cache[work_schedule_id] = timesheet_repository_->downloadWorkScheduleById(work_schedule_id);
        }
        const auto& work_schedule = work_schedules_cache[work_schedule_id];

        auto start_date = sys_days{year / January / 1};
        auto end_date = sys_days{year / December / 31};

        for (auto date = start_date; date <= end_date; date += std::chrono::days{1}) {
            TimesheetGenerationContext generation_context{system_administrator_id,
                                                          date,
                                                          employee_id,
                                                          department_id,
                                                          staff_position_id,
                                                          work_schedule_id,
                                                          work_schedule,
                                                          pre_holidays,
                                                          holidays,
                                                          extra_holidays,
                                                          vacations};

            if (generateEmployeeVacationsInTimesheet(timesheet, generation_context)) {
                continue;
            }

            if (generateHolidaysInTimesheet(timesheet, generation_context)) {
                continue;
            }

            generateWorkingDayInTimesheet(timesheet, generation_context);
        }
    }

    return timesheet_repository_->uploadTimesheet(timesheet);
}

bool TimesheetService::generateTimesheetForNewEmployee(const domain::Shop::EmployeeAssignment& employee_assignment,
                                                       const domain::Employee& employee) {
    using namespace std::chrono;
    using namespace std::literals;

    auto year = getCurrentData().year();

    domain::Timesheet timesheet;

    auto pre_holidays = timesheet_repository_->downloadPreHolidaysByYear(year);
    auto holidays = timesheet_repository_->downloadHolidaysByYear(year);
    auto extra_holidays = timesheet_repository_->downloadExtraHolidaysByYear(year);
    auto system_administrator_id = timesheet_repository_->downloadSystemAdministratorId();
    auto work_schedule = timesheet_repository_->downloadWorkScheduleById(employee_assignment.work_schedule_id);
    auto vacations = timesheet_repository_->downloadVacationsByEmployeeIdAndYear(employee.employee_id, year);

    auto start_date = sys_days{year / January / 1};
    auto end_date = sys_days{year / December / 31};

    for (auto date = start_date; date <= end_date; date += std::chrono::days{1}) {
        TimesheetGenerationContext generation_context{system_administrator_id,
                                                      date,
                                                      employee.employee_id,
                                                      employee_assignment.department_id,
                                                      employee_assignment.staff_position_id,
                                                      employee_assignment.work_schedule_id,
                                                      work_schedule,
                                                      pre_holidays,
                                                      holidays,
                                                      extra_holidays,
                                                      vacations};

        if (generateEmployeeVacationsInTimesheet(timesheet, generation_context)) {
            continue;
        }

        if (generateHolidaysInTimesheet(timesheet, generation_context)) {
            continue;
        }

        generateWorkingDayInTimesheet(timesheet, generation_context);
    }

    return timesheet_repository_->uploadTimesheet(timesheet);
}
