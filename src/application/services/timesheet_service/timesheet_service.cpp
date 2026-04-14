#include "timesheet_service.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/entities/timesheet/timesheet.h"
#include "domain/value_data/types.h"
#include "domain/entities/timesheet/leave_types/leave_type.h"

#include <chrono>
#include <unordered_map>
#include <exception>
#include <vector>

using namespace application;

std::optional<domain::Timesheet> TimesheetService::GetTimesheet(domain::DepartmentId department_id
                                                                , domain::AdminCategoryId admin_category_id
                                                                , std::chrono::year_month year_month) const {
   return timesheet_repository_->DownloadTimesheet(department_id, admin_category_id, year_month);
}

bool TimesheetService::GenerateEmployeeVacationsInTimesheet(domain::Timesheet& timesheet
                                                            , const TimesheetGenerationContext& generation_context) {
    auto it = generation_context.vacations.find(generation_context.employee_id);
    if (it == generation_context.vacations.end()){
        return false;
    }
    
    for (const auto& vacation : it -> second){
        if (vacation.IsVacationDay(generation_context.date)){
            auto vacation_day_data = domain::Timesheet::DayData::CreateNonWorkingDayData(
                domain::LeaveType::VACATION,
                generation_context.department_id,
                generation_context.staff_position_id,
                generation_context.work_schedule_id
            );
            timesheet.AddEmployeeDayData(generation_context.employee_id, generation_context.date,
                                                            generation_context.admin_category_id, vacation_day_data);
            return true;
        }
    }
}

bool TimesheetService::GenerateHolidaysInTimesheet(domain::Timesheet& timesheet
                                                    , const TimesheetGenerationContext& generation_context) {
    const auto& work_schedule_day_data = generation_context.work_schedule.GetDayDataByDate(generation_context.date);

    if (!generation_context.work_schedule.IsWorksOnHolidays()){
        if (generation_context.pre_holidays.contains(generation_context.date)){
            auto pre_holidays_day_data = domain::Timesheet::DayData::CreateWorkingDayData(
                work_schedule_day_data,
                generation_context.department_id,
                generation_context.staff_position_id,
                generation_context.work_schedule_id
            );

            pre_holidays_day_data.work_end.value() -= std::chrono::hours{1};
            pre_holidays_day_data.work_time.value() -= std::chrono::hours{1};

            timesheet.AddEmployeeDayData(
                generation_context.employee_id,
                generation_context.date,
                generation_context.admin_category_id,
                pre_holidays_day_data
            );
            return true;
        }
        else if (generation_context.holidays.contains(generation_context.date)){
            // Не добавляем день в табель
            return true;
        }
        else if (generation_context.extra_holidays.contains(generation_context.date)){
            // Не добавляем день в табель
            return true;
        }
    }
    return false;
}

bool TimesheetService::GenerateWorkingDayInTimesheet(domain::Timesheet& timesheet
                                                    , const TimesheetGenerationContext& generation_context) {
    const auto& work_schedule_day_data = generation_context.work_schedule.GetDayDataByDate(generation_context.date);

    if (work_schedule_day_data.IsWorkingDay()){
        auto working_day_data = domain::Timesheet::DayData::CreateWorkingDayData(
            work_schedule_day_data,
            generation_context.department_id,
            generation_context.staff_position_id,
            generation_context.work_schedule_id
        );

        timesheet.AddEmployeeDayData(
            generation_context.employee_id,
            generation_context.date,
            generation_context.admin_category_id,
            working_day_data
        );
        return true;
    }
    return false;
}

domain::Timesheet TimesheetService::GenerateTimesheet(const domain::Shop &shop, std::chrono::year year) {
    using namespace std::chrono;
    using namespace std::literals;
    using WorkSchedules = std::unordered_map<domain::WorkScheduleId, domain::WorkSchedule, domain::WorkScheduleIdHasher>;

    domain::Timesheet timesheet;
    WorkSchedules work_schedules_cache;

    const auto& employees_assignments = shop.GetEmployeeAssignments();

    auto pre_holidays = timesheet_repository_->DownloadPreHolidaysByYear(year);
    auto holidays = timesheet_repository_->DownloadHolidaysByYear(year);
    auto extra_holidays = timesheet_repository_->DownloadExtraHolidaysByYear(year);
    auto vacations = timesheet_repository_->DownloadVacationsByShopAndYear(shop, year);
    auto system_administrator_id = timesheet_repository_->DownloadSystemAdministratorId();
    
    for (const auto& [employee_id, employee_assignment] : employees_assignments){
        const auto& work_schedule_id = employee_assignment.work_schedule_id;
        const auto& department_id = employee_assignment.department_id;
        const auto& staff_position_id = employee_assignment.staff_position_id;

        if (!work_schedules_cache.contains(work_schedule_id)){
            work_schedules_cache[work_schedule_id] = timesheet_repository_->DownloadWorkScheduleById(work_schedule_id);
        }
        const auto& work_schedule = work_schedules_cache[work_schedule_id];
        
        auto start_date = sys_days{year / January / 1};
        auto end_date = sys_days{year / December / 31};

        for (auto date = start_date; date <= end_date; date += std::chrono::days{1}){
            TimesheetGenerationContext generation_context{system_administrator_id, date, employee_id, department_id
                                                            , staff_position_id, work_schedule_id, work_schedule, pre_holidays
                                                            , holidays, extra_holidays, vacations};
        
            if (GenerateEmployeeVacationsInTimesheet(timesheet, generation_context)){
                continue;
            }

            if (GenerateHolidaysInTimesheet(timesheet, generation_context)){
                continue;
            }

            GenerateWorkingDayInTimesheet(timesheet, generation_context);
        }
    }   
    return timesheet;
}

bool TimesheetService::AddTimesheet(const domain::Timesheet &timesheet) {
    return timesheet_repository_->UploadTimesheet(timesheet);
}
