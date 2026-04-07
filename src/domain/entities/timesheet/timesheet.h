#pragma once

#include "domain/value_data/types.h"
#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/department/department.h"
#include "domain/entities/shop/staff_position/staff_position.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"
#include "domain/entities/timesheet/leave_types/leave_type.h"
#include "domain/entities/timesheet/admin_categorys/admin_category.h"
#include "domain/entities/shop/shop.h"

#include <string>
#include <optional>
#include <unordered_map>
#include <utility>

namespace domain {

class Timesheet {
public:
    struct DayDataKey {
        std::chrono::year_month_day date;
        AdminCategoryId admin_category_id;

        bool operator==(const DayDataKey& other) const {
            return date == other.date && admin_category_id == other.admin_category_id;
        }
    };

    struct DayDataKeyHasher {
        size_t operator()(const DayDataKey& key) const {
            auto date_year_hash = std::hash<int>{}(static_cast<int>(key.date.year()));
            auto date_month_hash = std::hash<unsigned>{}(static_cast<unsigned>(key.date.month()));
            auto date_day_hash = std::hash<unsigned>{}(static_cast<unsigned>(key.date.day()));
            auto admin_category_id_hash = AdminCategoryIdHasher{}(key.admin_category_id);

            size_t hash = date_year_hash;
            hash ^= date_month_hash << 1;
            hash ^= date_day_hash << 1;
            hash ^= admin_category_id_hash << 1;
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

        static DayData CreateWorkingDayData(const WorkSchedule::DayData& work_schedule_day_data
                                            , DepartmentId department_id, StaffPositionId staff_position_id
                                            , WorkScheduleId work_schedule_id);
        static DayData CreateNonWorkingDayData(LeaveType leave_type
                                                , DepartmentId department_id, StaffPositionId staff_position_id
                                                , WorkScheduleId work_schedule_id);
        

        bool IsWorkingDay() const noexcept;
        bool IsNightWorkingDay() const noexcept;
    };

    using DaysData = std::unordered_map<DayDataKey, domain::Timesheet::DayData>;
    using TimesheetData = std::unordered_map<domain::EmployeeId, DaysData, domain::EmployeeIdHasher>;

    bool IsEmpty() const;
    bool AddEmployeeDayData(EmployeeId employee_id, domain::Date date
                            , AdminCategoryId admin_category_id, const DayData& day_data);

private:
    TimesheetData data_;
};
    
} // namespace domain
