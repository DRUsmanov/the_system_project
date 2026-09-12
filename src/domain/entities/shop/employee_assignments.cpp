#include "entities/shop/employee_assignments.h"

const domain::EmployeeAssignments::Container& domain::EmployeeAssignments::getEmployeeAssignments() const {
    return employee_assignments_;
}