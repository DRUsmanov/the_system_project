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
    EmployeeAssignments() = default;
    EmployeeAssignments(EmployeeAssignments&& other_employee_assignments) :
        employee_assignments_{std::move(other_employee_assignments.employee_assignments_)} {}

    using Assignments = std::unordered_map<EmployeeId, EmployeeAssignment, EmployeeIdHasher>;

    const EmployeeAssignments::Assignments& getEmployeeAssignments() const;
    void addEmployeeAssignment(EmployeeId employee_id, const EmployeeAssignment& employee_assignment);

protected:
    Assignments employee_assignments_;
};

}  // namespace domain
