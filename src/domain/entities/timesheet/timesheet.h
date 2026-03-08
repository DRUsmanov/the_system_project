#pragma once

#include "domain/value_data/types.h"
#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/department/department.h"
#include "domain/entities/shop/staff_position/staff_position.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/entities/timesheet/leave_types/leave_type.h"
#include "domain/entities/timesheet/administrators/administrator.h"

#include <string>
#include <optional>
#include <unordered_map>
#include <utility>

namespace domain {

class Timesheet {
public:
    struct Key {
        std::chrono::year_month_day date;
        AdministratorId administrator_id;

        bool operator==(const Key& other) const {
            return date == other.date && administrator_id == other.administrator_id;
        }
    };

    struct KeyHasher {
        size_t operator()(const Key& key) const {
            auto date_year_hash = std::hash<int>{}(static_cast<int>(key.date.year()));
            auto date_month_hash = std::hash<unsigned>{}(static_cast<unsigned>(key.date.month()));
            auto date_day_hash = std::hash<unsigned>{}(static_cast<unsigned>(key.date.day()));
            auto administrator_id_hash = AdministratorIdHasher{}(key.administrator_id);

            size_t hash = date_year_hash;
            hash ^= date_month_hash << 1;
            hash ^= date_day_hash << 1;
            hash ^= administrator_id_hash << 1;
            return hash;
        }
    };

    struct DayData {
        DepartmentId department_id;
        StaffPositionId staff_position_id;
        WorkScheduleId work_schedule_id;
        std::optional<Time> work_time;
        std::optional<Time> night_work_time;
        LeaveTypeId leave_type_id;
        std::string comment;

        bool IsWorkingDay() const noexcept{
            return work_time.has_value();
        }

        bool IsNightWorkingDay() const noexcept {
            return night_work_time.has_value();
        }
    };

    bool AddEmployeeDayData(EmployeeId employee_id, std::chrono::year_month_day day, AdministratorId administrator_id, const DayData& day_data);

    using DaysData = std::unordered_map<Key, domain::Timesheet::DayData>;
    using TimesheetData = std::unordered_map<domain::EmployeeId, DaysData, domain::EmployeeIdHasher>;

private:
    TimesheetData data_;
};
    
} // namespace domain
