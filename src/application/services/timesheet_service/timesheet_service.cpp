#include "timesheet_service.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/entities/timesheet/timesheet.h"
#include "domain/value_data/types.h"

#include <chrono>
#include <unordered_map>
#include <exception>

domain::Timesheet application::TimeSheetService::GenerateTimeSheet(const domain::Shop& shop, std::chrono::year year) {
    try{
        using namespace std::chrono;
        using namespace std::literals;
        using WorkSchedulesDaysData = std::unordered_map<domain::WorkScheduleId, domain::Timesheet::DaysData, domain::WorkScheduleIdHasher>;
        
        auto start_date = sys_days{year / January / 1};
        auto end_date = sys_days{year / December / 31};

        // Формируем табель для всех графиков



        auto work_schedules = timesheet_repository_.GetWorkSchedules();
        auto holidays = timesheet_repository_.GetHolidays(year);
        auto extra_holidays = timesheet_repository_.GetExtraHolidays(year);
        auto pre_holidays = timesheet_repository_.GetPreHolidays(year);
        auto system_admnistrator_id = timesheet_repository_.GetSystemAdministratorId();

        WorkSchedulesDaysData work_schedules_days_data;

        for (auto date = start_date; date <= end_date; date += days{1}) {
            for (const auto& [work_schedule_id, work_schedule] : work_schedules){
                auto work_schedule_start_cycle_date = sys_days{work_schedule.GetStartCycleDate()};
                auto day_index = (date - work_schedule_start_cycle_date).count() % work_schedule.GetCycleSize();
                auto work_schedule_day_data = work_schedule[day_index];

                domain::Timesheet::DayData timesheet_day_data;
                if (!work_schedule[day_index].IsWorkingDay()){
                    // Пропускаем день
                    continue;
                }
                else if (!work_schedule.IsWorksOnHolidays() && holidays.contains(date)){
                    // Пропускаем день
                    continue;
                }
                else if (!work_schedule.IsWorksOnHolidays() && extra_holidays.contains(date)) {
                    // Пропускаем день
                    continue;
                }
                else if (!work_schedule.IsWorksOnHolidays() && pre_holidays.contains(date)) {
                    auto new_work_time = domain::Time{
                        duration_cast<minutes>(work_schedule_day_data.work_time.value().to_duration() - domain::Time{60min}.to_duration())
                    };
                    timesheet_day_data.work_time = new_work_time;
                    timesheet_day_data.night_work_time = std::nullopt;
                }
                else {
                    timesheet_day_data.work_time = work_schedule_day_data.work_time;
                    timesheet_day_data.night_work_time = work_schedule_day_data.night_work_time;
                }
                timesheet_day_data.work_schedule_id = work_schedule_id;
                domain::Timesheet::Key key{date, system_admnistrator_id};
                work_schedules_days_data[work_schedule_id][key] = timesheet_day_data;
            }
        }
        return true;
    }
    catch (const std::exception& ex){
        return false;
    }
}