#pragma once

#include <unordered_map>

#include "entities/shop/department/department.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/staff_position/staff_position.h"
#include "entities/timesheet/work_schedules/work_schedule.h"

namespace domain {

class Shop {
public:
    struct EmployeeAssignment {
        DepartmentId department_id;
        StaffPositionId staff_position_id;
        WorkScheduleId work_schedule_id;
    };

    using EmployeeAssignments = std::unordered_map<EmployeeId, EmployeeAssignment, EmployeeIdHasher>;

    const EmployeeAssignments& getEmployeeAssignments() const;

private:
    EmployeeAssignments employee_assignments_;
};

}  // namespace domain
