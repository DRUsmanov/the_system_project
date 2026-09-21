#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "entities/shop/department/department.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments/employee_assignments.h"
#include "entities/shop/staff_position/staff_position.h"
#include "entities/timesheet/admin_categorys/admin_category.h"
#include "entities/timesheet/leave_types/leave_type.h"
#include "entities/timesheet/work_schedules/work_schedule.h"
#include "value_data/types.h"

namespace domain {

class Timesheet {
public:
    struct DayDataKey {
        std::chrono::year_month_day date;

        bool operator==(const DayDataKey& other) const {
            return date == other.date;
        }
    };

    struct DayDataKeyHasher {
        size_t operator()(const DayDataKey& key) const {
            auto date_year_hash = std::hash<int>{}(static_cast<int>(key.date.year()));
            auto date_month_hash = std::hash<unsigned>{}(static_cast<unsigned>(key.date.month()));
            auto date_day_hash = std::hash<unsigned>{}(static_cast<unsigned>(key.date.day()));

            size_t hash = date_year_hash;
            hash ^= date_month_hash << 1;
            hash ^= date_day_hash << 1;
            return hash;
        }
    };

    struct DayData {
        DepartmentId department_id;
        StaffPositionId staff_position_id;
        WorkScheduleId work_schedule_id;

        std::optional<Time> work_start;
        std::optional<Time> work_end;
        std::optional<Time> work_time;
        std::optional<Time> night_work_start;
        std::optional<Time> night_work_end;
        std::optional<Time> night_work_time;
        std::optional<Time> rest_start;
        std::optional<Time> rest_end;

        std::optional<LeaveType> leave_type;
        std::optional<std::string> comment;

        static DayData createWorkingDayData(const WorkSchedule::DayData& work_schedule_day_data,
                                            DepartmentId department_id,
                                            StaffPositionId staff_position_id,
                                            WorkScheduleId work_schedule_id);
        static DayData createNonWorkingDayData(LeaveType leave_type,
                                               DepartmentId department_id,
                                               StaffPositionId staff_position_id,
                                               WorkScheduleId work_schedule_id);

        bool isWorkingDay() const noexcept;
        bool isNightWorkingDay() const noexcept;
    };

    using DaysData = std::unordered_map<Date, Timesheet::DayData, DateHasher>;
    using TimesheetData = std::unordered_map<EmployeeId, DaysData, EmployeeIdHasher>;

    bool addEmployeeDayData(EmployeeId employee_id,
                            Date date,
                            AdminCategoryId admin_category_id,
                            const DayData& day_data);
    std::optional<DayData> getEmployeeDayData(EmployeeId employee_id, Date date) const;
    bool changeEmployeeDayData(EmployeeId employee_id, Date date, const DayData& day_data);

    TimesheetData::const_iterator begin() const;
    TimesheetData::const_iterator end() const;

private:
    TimesheetData data_;
};

}  // namespace domain
