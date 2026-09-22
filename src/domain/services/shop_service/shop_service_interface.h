#pragma once

#include <chrono>
#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments/employee_assignments.h"

namespace domain {

class ShopServiceInterface {
public:
    virtual ~ShopServiceInterface() = default;

    virtual std::optional<EmployeeAssignments> getAllEmployeeAssignments() const = 0;
    virtual std::optional<EmployeeId> addNewEmployee(const Employee& employee,
                                                     const EmployeeAssignment& employee_assignment) = 0;
    virtual std::optional<Employee> getEmployee(const EmployeeId& employee_id) const = 0;
    virtual std::optional<EmployeeAssignment> getEmployeeAssignment(const EmployeeId& employee_id) const = 0;
    virtual std::optional<EmployeeAssignments> getDepartmentAssignments(const DepartmentId& department_id) const = 0;
    virtual bool removeEmployee(const EmployeeId& employee_id) const = 0;
    virtual std::optional<Departments> getDepartments() const = 0;
    virtual std::optional<StaffPositions> getStaffPositions() const = 0;
    virtual bool updateEmployee(const EmployeeId& employee_id,
                                const Employee& employee,
                                const EmployeeAssignment& employee_assignment) = 0;
};

}  // namespace domain
