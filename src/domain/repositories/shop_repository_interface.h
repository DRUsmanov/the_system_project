#pragma once

#include <optional>
#include <vector>

#include "entities/shop/employee/employee.h"
#include "entities/shop/shop.h"

namespace domain {

class ShopRepositoryInterface {
public:
    virtual ~ShopRepositoryInterface() = default;

    virtual Shop downloadShop() const = 0;
    virtual std::optional<EmployeeId> uploadEmployee(const Employee& employee,
                                                     DepartmentId department_id,
                                                     StaffPositionId staff_position_id,
                                                     WorkScheduleId work_schedule_id) = 0;
    virtual std::optional<Employee> downloadEmployee(EmployeeId employee_id) const = 0;
    virtual std::optional<Shop::EmployeeAssignment> downloadEmployeeAssignment(EmployeeId employee_id) const = 0;
    virtual bool removeEmployee(EmployeeId employee_id) = 0;
    virtual std::optional<Departments> downloadDepartments() const = 0;
    virtual std::optional<StaffPositions> downloadStaffPositions() const = 0;
};

}  // namespace domain
