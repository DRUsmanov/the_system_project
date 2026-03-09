#include "timesheet.h"

#include <exception>

bool domain::Timesheet::IsEmpty() const {
    return data_.empty();
}

bool domain::Timesheet::AddEmployeeDayData(EmployeeId employee_id, std::chrono::year_month_day day,
                                           AdministratorId administrator_id, const DayData &day_data)
{
    try {
        auto& employee_days_data = data_[employee_id];
        auto [it, inserted] = employee_days_data.try_emplace(Key{day, administrator_id}, day_data);
        return inserted;
    }
    catch (const std::exception& ex){
        return false;
    }
}