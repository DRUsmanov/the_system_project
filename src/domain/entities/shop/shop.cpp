#include "shop.h"

const domain::Shop::EmployeeAssignments& domain::Shop::GetEmployeeAssignments() const {
    return employee_assignments_;
}