#include "timesheet.h"

#include <exception>

bool domain::Timesheet::AddEmployeeDayData(EmployeeId employee_id, std::chrono::year_month_day day,
    AdministratorId administrator_id, const DayData& day_data) {
    try {
        if (data_.contains(employee_id)
        && data_[employee_id].contains(day)
        && data_[employee_id][day].administrator_id == day_data.administrator_id){
            // Если запись для работника на этот день от данного администратора существует
            return false;
        }
        data_[employee_id][day] = day_data;
        return true;
    }
    catch (const std::exception& ex){
        return false;
    }
}