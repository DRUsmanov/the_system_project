#include "entities/timesheet/timesheet.h"

#include <exception>

bool domain::Timesheet::addEmployeeDayData(EmployeeId employee_id,
                                           domain::Date date,
                                           AdminCategoryId admin_category_id,
                                           const DayData& day_data) {
    auto& employee_days_data = data_[employee_id];
    auto [it, inserted] = employee_days_data.try_emplace(date, day_data);
    return inserted;
}

std::optional<domain::Timesheet::DayData> domain::Timesheet::getEmployeeDayData(EmployeeId employee_id,
                                                                                Date date) const {
    auto employee_days_data_it = data_.find(employee_id);
    if (employee_days_data_it == data_.end()) {
        return std::nullopt;
    }

    const auto& employee_days_data = employee_days_data_it->second;

    auto employee_day_data_it = employee_days_data.find(date);
    if (employee_day_data_it == employee_days_data.end()) {
        return std::nullopt;
    }

    const auto& employee_day_data = employee_day_data_it->second;

    return employee_day_data;
}

bool domain::Timesheet::changeEmployeeDayData(EmployeeId employee_id, Date date, const DayData& day_data) {
    auto employee_days_data_it = data_.find(employee_id);
    if (employee_days_data_it == data_.end()) {
        return false;
    }

    auto& employee_days_data = employee_days_data_it->second;

    auto employee_day_data_it = employee_days_data.find(date);
    if (employee_day_data_it == employee_days_data.end()) {
        return false;
    }

    auto& employee_day_data = employee_day_data_it->second;

    employee_day_data = day_data;

    return true;
}

domain::Timesheet::TimesheetData::const_iterator domain::Timesheet::begin() const {
    return data_.begin();
}

domain::Timesheet::TimesheetData::const_iterator domain::Timesheet::end() const {
    return data_.end();
}

domain::Timesheet::DayData domain::Timesheet::DayData::createWorkingDayData(
    const WorkSchedule::DayData& work_schedule_day_data,
    DepartmentId department_id,
    StaffPositionId staff_position_id,
    WorkScheduleId work_schedule_id) {
    DayData working_day_data;

    working_day_data.department_id = department_id;
    working_day_data.staff_position_id = staff_position_id;
    working_day_data.work_schedule_id = work_schedule_id;

    working_day_data.work_start = work_schedule_day_data.work_start;
    working_day_data.work_end = work_schedule_day_data.work_end;
    working_day_data.work_time = work_schedule_day_data.work_time;

    working_day_data.night_work_start = work_schedule_day_data.night_work_start;
    working_day_data.night_work_end = work_schedule_day_data.night_work_end;
    working_day_data.night_work_time = work_schedule_day_data.night_work_time;

    working_day_data.rest_start = work_schedule_day_data.rest_start;
    working_day_data.rest_end = work_schedule_day_data.rest_end;

    working_day_data.leave_type = std::nullopt;
    working_day_data.comment = std::nullopt;

    return working_day_data;
}

domain::Timesheet::DayData domain::Timesheet::DayData::createNonWorkingDayData(LeaveType leave_type,
                                                                               DepartmentId department_id,
                                                                               StaffPositionId staff_position_id,
                                                                               WorkScheduleId work_schedule_id) {
    DayData non_working_day_data;

    non_working_day_data.department_id = department_id;
    non_working_day_data.staff_position_id = staff_position_id;
    non_working_day_data.work_schedule_id = work_schedule_id;

    non_working_day_data.work_start = std::nullopt;
    non_working_day_data.work_end = std::nullopt;
    non_working_day_data.work_time = std::nullopt;

    non_working_day_data.night_work_start = std::nullopt;
    non_working_day_data.night_work_end = std::nullopt;
    non_working_day_data.night_work_time = std::nullopt;

    non_working_day_data.rest_start = std::nullopt;
    non_working_day_data.rest_end = std::nullopt;

    non_working_day_data.leave_type = leave_type;
    non_working_day_data.comment = std::nullopt;

    return non_working_day_data;
}

bool domain::Timesheet::DayData::isWorkingDay() const noexcept {
    return work_time.has_value();
}

bool domain::Timesheet::DayData::isNightWorkingDay() const noexcept {
    return night_work_time.has_value();
}
