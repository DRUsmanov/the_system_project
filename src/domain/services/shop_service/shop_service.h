#pragma once

#include <chrono>
#include <memory>

#include "repositories/shop_repository_interface.h"
#include "services/shop_service/shop_service_interface.h"

namespace domain {

class ShopService : public ShopServiceInterface {
public:
    ShopService(std::shared_ptr<ShopRepositoryInterface> shop_repository) : shop_repository_{shop_repository} {}

    EmployeeAssignments getAllEmployeeAssignments() const override;
    std::optional<EmployeeId> addNewEmployee(const Employee& employee,
                                             const EmployeeAssignment& employee_assignment) override;
    std::optional<Employee> getEmployee(const EmployeeId& employee_id) const override;
    std::optional<EmployeeAssignment> getEmployeeAssignment(const EmployeeId& employee_id) const override;
    std::optional<EmployeeAssignments> getDepartmentAssignments(const DepartmentId& department_id) const override;
    bool removeEmployee(const EmployeeId& employee_id) const override;
    std::optional<Departments> getDepartments() const override;
    std::optional<StaffPositions> getStaffPositions() const override;
    bool updateEmployee(const EmployeeId& employee_id,
                        const Employee& employee,
                        const EmployeeAssignment& employee_assignment) override;

private:
    std::shared_ptr<ShopRepositoryInterface> shop_repository_;
};

}  // namespace domain
