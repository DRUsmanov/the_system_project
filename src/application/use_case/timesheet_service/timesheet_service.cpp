#include "timesheet_service.h"

#include <chrono>

bool application::TimeSheetService::GenerateTimeSheet(int year)
{
    using namespace std::chrono;
    auto start_date = std::chrono::year(year) / January / 01;
    auto end_date = std::chrono::year(year) / December / 31;

    auto schedules_table = timesheet_repository_.GetShedulesTable();

    for (auto date = sys_days{start_date}; date <= sys_days{end_date}; date += days{1}){
        
    }
    return false;
}