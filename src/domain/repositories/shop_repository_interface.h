#pragma once

#include <optional>
#include <vector>

#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments/employee_assignments.h"

namespace domain {

class ShopRepositoryInterface {
public:
    virtual ~ShopRepositoryInterface() = default;

    virtual std::optional<EmployeeAssignments> downloadAllEmployeeAssignments() const = 0;
    virtual std::optional<EmployeeId> uploadEmployee(const Employee& employee,
                                                     const EmployeeAssignment& employee_assignment) = 0;
    virtual std::optional<Employee> downloadEmployee(EmployeeId employee_id) const = 0;
    virtual std::optional<EmployeeAssignment> downloadEmployeeAssignment(EmployeeId employee_id) const = 0;
    virtual bool removeEmployee(EmployeeId employee_id) = 0;
    virtual std::optional<Departments> downloadDepartments() const = 0;
    virtual std::optional<StaffPositions> downloadStaffPositions() const = 0;
    virtual std::optional<EmployeeAssignments> downloadDepartmentAssignments(DepartmentId department_id) const = 0;
    virtual bool updateEmployee(const EmployeeId& employee_id, const Employee& employee) = 0;
    virtual bool updateEmployeeAssignment(const EmployeeId& employee_id,
                                          const EmployeeAssignment& employee_assignment) = 0;
};

}  // namespace domain
