#pragma once

#include "repositories/shop_repository_interface.h"
#include "uow_impl/uow_impl.h"

namespace infrastructure {

class ShopRepository : public domain::ShopRepositoryInterface {
public:
    ShopRepository(std::shared_ptr<Uow> uow) : uow_{uow} {}

    std::optional<domain::EmployeeAssignments> downloadAllEmployeeAssignments() const override;
    std::optional<domain::EmployeeId> uploadEmployee(const domain::Employee& employee,
                                                     const domain::EmployeeAssignment& employee_assignment) override;
    std::optional<domain::Employee> downloadEmployee(domain::EmployeeId employee_id) const override;
    std::optional<domain::EmployeeAssignment> downloadEmployeeAssignment(domain::EmployeeId employee_id) const override;
    bool removeEmployee(domain::EmployeeId employee_id) override;
    std::optional<domain::Departments> downloadDepartments() const override;
    std::optional<domain::StaffPositions> downloadStaffPositions() const override;
    std::optional<domain::EmployeeAssignments> downloadDepartmentAssignments(
        domain::DepartmentId department_id) const override;
    bool updateEmployee(const domain::EmployeeId& employee_id, const domain::Employee& employee) override;
    bool updateEmployeeAssignment(const domain::EmployeeId& employee_id,
                                  const domain::EmployeeAssignment& employee_assignment) override;

private:
    std::shared_ptr<Uow> uow_;
};

}  // namespace infrastructure
