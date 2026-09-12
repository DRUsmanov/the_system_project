#pragma once

#include <chrono>
#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments.h"

namespace domain {

class ShopServiceInterface {
public:
    virtual ~ShopServiceInterface() = default;

    virtual EmployeeAssignments getAllEmployeeAssignments() const = 0;
    virtual std::optional<EmployeeId> addNewEmployee(EmployeeAssignment employee_assignment,
                                                     const Employee& employee) = 0;
    virtual std::optional<Employee> getEmployee(EmployeeId employee_id) const = 0;
    virtual std::optional<EmployeeAssignment> getEmployeeAssignment(EmployeeId employee_id) const = 0;
    virtual bool removeEmployee(EmployeeId employee_id) const = 0;
    virtual std::optional<Departments> getDepartments() const = 0;
    virtual std::optional<StaffPositions> getStaffPositions() const = 0;
};

}  // namespace domain
