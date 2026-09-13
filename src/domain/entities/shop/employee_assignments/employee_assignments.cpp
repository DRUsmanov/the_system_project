#include "entities/shop/employee_assignments/employee_assignments.h"

const domain::EmployeeAssignments::Assignments& domain::EmployeeAssignments::getEmployeeAssignments() const {
    return employee_assignments_;
}

void domain::EmployeeAssignments::addEmployeeAssignment(EmployeeId employee_id,
                                                        const EmployeeAssignment& employee_assignment) {
    employee_assignments_.insert({employee_id, employee_assignment});
}
