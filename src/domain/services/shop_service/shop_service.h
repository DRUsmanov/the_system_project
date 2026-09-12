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
    std::optional<EmployeeId> addNewEmployee(EmployeeAssignment employee_assignment, const Employee& employee) override;
    std::optional<Employee> getEmployee(EmployeeId employee_id) const override;
    std::optional<EmployeeAssignment> getEmployeeAssignment(EmployeeId employee_id) const override;
    bool removeEmployee(EmployeeId employee_id) const override;
    std::optional<Departments> getDepartments() const override;
    std::optional<StaffPositions> getStaffPositions() const override;

private:
    std::shared_ptr<ShopRepositoryInterface> shop_repository_;
};

}  // namespace domain
