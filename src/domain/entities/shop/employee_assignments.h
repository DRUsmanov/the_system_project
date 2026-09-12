#pragma once

#include <unordered_map>

#include "entities/shop/department/department.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/staff_position/staff_position.h"
#include "entities/timesheet/work_schedules/work_schedule.h"

namespace domain {

struct EmployeeAssignment {
    DepartmentId department_id;
    StaffPositionId staff_position_id;
    WorkScheduleId work_schedule_id;
};

class EmployeeAssignments {
public:
    using Container = std::unordered_map<EmployeeId, EmployeeAssignment, EmployeeIdHasher>;

    const EmployeeAssignments::Container& getEmployeeAssignments() const;

private:
    Container employee_assignments_;
};

}  // namespace domain
