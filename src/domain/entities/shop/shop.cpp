#include "entities/shop/shop.h"

const domain::Shop::EmployeeAssignments& domain::Shop::getEmployeeAssignments() const {
    return employee_assignments_;
}