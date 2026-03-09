#pragma once

#include "domain/entities/shop/department/department.h"
#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/staff_position/staff_position.h"
#include "domain/entities/timesheet/work_schedules/work_schedule.h"

#include <unordered_map>

namespace domain {

class Shop {
public:
    struct EmployeeAssignment {
        DepartmentId department_id;
        StaffPositionId staff_position_id;
        WorkScheduleId work_schedule_id;
    };

    using ShopData = std::unordered_map<EmployeeId, EmployeeAssignment, EmployeeIdHasher>;

    const ShopData& GetData() const;
    
private:
    ShopData data_;
};
    
} // namespace domain
