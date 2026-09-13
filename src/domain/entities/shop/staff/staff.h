#pragma once

#include <unordered_map>

#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments/employee_assignments.h"

namespace domain {

class Staff : public EmployeeAssignments {
public:
    Staff(EmployeeAssignments&& employee_assignments) : EmployeeAssignments{std::move(employee_assignments)} {}
    using Employees = std::unordered_map<EmployeeId, Employee, EmployeeIdHasher>;

    Employees getEmployees() const;
    void addEmployee(const EmployeeId employee_id, const Employee& employee);

private:
    Employees employees_;
};

}  // namespace domain
