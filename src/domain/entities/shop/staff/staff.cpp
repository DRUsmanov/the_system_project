#include "entities/shop/staff/staff.h"

const domain::Employees& domain::Staff::getEmployees() const {
    return employees_;
}

void domain::Staff::addEmployee(const EmployeeId employee_id, const Employee& employee) {
    employees_.insert({employee_id, employee});
}
