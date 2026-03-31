#include "timesheet.h"

#include <exception>

bool domain::Timesheet::IsEmpty() const {
    return data_.empty();
}

bool domain::Timesheet::AddEmployeeDayData(EmployeeId employee_id, std::chrono::year_month_day day,
                                           AdministratorId administrator_id, const DayData &day_data) {
    try {
        auto& employee_days_data = data_[employee_id];
        auto [it, inserted] = employee_days_data.try_emplace(DayDataKey{day, administrator_id}, day_data);
        return inserted;
    }
    catch (const std::exception& ex){
        return false;
    }
}

// Конструктор подразумевает создание только рабочих дней на основании графика
domain::Timesheet::DayData::DayData(const WorkSchedule::DayData& work_schedule_day_data
                        , DepartmentId department_id, StaffPositionId staff_position_id
                        , WorkScheduleId work_schedule_id) {
    this->department_id = department_id;
    this->staff_position_id = staff_position_id;
    this->work_schedule_id = work_schedule_id;

    work_start = work_schedule_day_data.work_start;
    work_end = work_schedule_day_data.work_end;
    work_time = work_schedule_day_data.work_time;

    night_work_start = work_schedule_day_data.night_work_start;
    night_work_end = work_schedule_day_data.night_work_end;
    night_work_time = work_schedule_day_data.night_work_time;

    rest_start = work_schedule_day_data.rest_start;
    rest_end = work_schedule_day_data.rest_end;

    leave_type = std::nullopt;
    comment = std::nullopt;
}

domain::Timesheet::DayData::DayData(LeaveType leave_type) {

}

bool domain::Timesheet::DayData::IsWorkingDay() const noexcept {
    return work_time.has_value();
}

bool domain::Timesheet::DayData::IsNightWorkingDay() const noexcept {
    return night_work_time.has_value();
}
