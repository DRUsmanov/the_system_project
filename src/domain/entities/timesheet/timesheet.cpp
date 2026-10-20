#include "entities/timesheet/timesheet.h"

#include <exception>
#include <iostream>

bool domain::Timesheet::addEmployeeDayData(const EmployeeId& employee_id, domain::Date date, const DayData& day_data) {
    auto& employee_days_data = data_[employee_id];
    auto [it, inserted] = employee_days_data.try_emplace(date, day_data);
    return inserted;
}

std::optional<domain::Timesheet::DayData> domain::Timesheet::getEmployeeDayData(const EmployeeId& employee_id,
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

std::optional<std::reference_wrapper<domain::Timesheet::DaysData>> domain::Timesheet::getEmployeeDaysData(
    const EmployeeId& employee_id) {
    if (data_.contains(employee_id)) {
        return data_[employee_id];
    }
    return std::nullopt;
}

std::optional<std::reference_wrapper<const domain::Timesheet::DaysData>> domain::Timesheet::getEmployeeDaysData(
    const EmployeeId& employee_id) const {
    if (data_.contains(employee_id)) {
        return data_.at(employee_id);
    }
    return std::nullopt;
}

bool domain::Timesheet::changeEmployeeDayData(const EmployeeId& employee_id, Date date, const DayData& day_data) {
    // not changing assignment
    if (!day_data.isValid()) {
        std::cout << "HERE1" << std::endl;
        return false;
    }

    auto employee_days_data_it = data_.find(employee_id);
    if (employee_days_data_it == data_.end()) {
        std::cout << "HERE2" << std::endl;
        return false;
    }

    auto& employee_days_data = employee_days_data_it->second;

    auto employee_day_data_it = employee_days_data.find(date);
    if (employee_day_data_it == employee_days_data.end()) {
        std::cout << "HERE3" << std::endl;
        return false;
    }

    auto& employee_day_data = employee_day_data_it->second;

    employee_day_data.work_start = day_data.work_start;
    employee_day_data.work_end = day_data.work_end;
    employee_day_data.work_time = day_data.work_time;
    employee_day_data.night_work_start = day_data.night_work_start;
    employee_day_data.night_work_end = day_data.night_work_end;
    employee_day_data.night_work_time = day_data.night_work_time;
    employee_day_data.rest_start = day_data.rest_start;
    employee_day_data.rest_end = day_data.rest_end;
    employee_day_data.leave_type = std::nullopt;
    employee_day_data.comment = day_data.comment;

    return employee_day_data.isValid();
}

bool domain::Timesheet::changeEmployeeAssignment(const EmployeeId& employee_id,
                                                 Date date,
                                                 const EmployeeAssignment& employee_assignment) {
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

    employee_day_data.department_id = employee_assignment.department_id;
    employee_day_data.staff_position_id = employee_assignment.staff_position_id;
    employee_day_data.work_schedule_id = employee_assignment.work_schedule_id;

    return true;
}

domain::Timesheet::TimesheetData::const_iterator domain::Timesheet::begin() const noexcept {
    return data_.begin();
}

domain::Timesheet::TimesheetData::const_iterator domain::Timesheet::end() const noexcept {
    return data_.end();
}

domain::Timesheet::TimesheetData::iterator domain::Timesheet::begin() noexcept {
    return data_.begin();
}

domain::Timesheet::TimesheetData::iterator domain::Timesheet::end() noexcept {
    return data_.end();
}

bool domain::Timesheet::empty() const noexcept {
    return data_.empty();
}

size_t domain::Timesheet::size() const noexcept {
    return data_.size();
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

void domain::Timesheet::DayData::setLeaveType(LeaveType leave_type) {
    work_start = std::nullopt;
    work_end = std::nullopt;
    work_time = std::nullopt;

    night_work_start = std::nullopt;
    night_work_end = std::nullopt;
    night_work_time = std::nullopt;

    rest_start = std::nullopt;
    rest_end = std::nullopt;

    leave_type = leave_type;
    comment = std::nullopt;
}

void domain::Timesheet::DayData::setComment(std::string comment) {
    comment = comment;
}

bool domain::Timesheet::DayData::isValid() const noexcept {
    // 1. Нерабочий день не должен иметь рабочих полей
    if (leave_type.has_value() &&
        (work_start.has_value() || work_end.has_value() || work_time.has_value() || night_work_start.has_value() ||
         night_work_end.has_value() || night_work_time.has_value() || rest_start.has_value() || rest_end.has_value())) {
        return false;
    }

    // 2. Пары start/end должны быть заданы вместе
    if (work_start.has_value() != work_end.has_value()) {
        return false;
    }
    if (night_work_start.has_value() != night_work_end.has_value()) {
        return false;
    }
    if (rest_start.has_value() != rest_end.has_value()) {
        return false;
    }

    // 3. Расчёт времени отдыха
    Time rest_time{0};
    if (rest_start.has_value()) {
        rest_time = rest_end.value() - rest_start.value();
        if (rest_time < Time{0}) {
            return false;
        }
    }

    // 4. Проверка рабочего времени
    if (work_time.has_value()) {
        if (!work_start.has_value() || !work_end.has_value()) {
            return false;
        }
        if ((work_end.value() - work_start.value() - rest_time) != work_time.value()) {
            return false;
        }
    }

    // 5. Проверка ночного времени
    if (night_work_time.has_value()) {
        if (!night_work_start.has_value() || !night_work_end.has_value()) {
            return false;
        }
        if ((night_work_end.value() - night_work_start.value()) != night_work_time.value()) {
            return false;
        }
    }

    return true;
}
