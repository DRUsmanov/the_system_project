#include "services/shop_service/shop_service.h"

#include "logger.h"

using namespace domain;

std::optional<EmployeeAssignments> ShopService::getAllEmployeeAssignments() const {
    return shop_repository_->downloadAllEmployeeAssignments();
}

std::optional<EmployeeId> ShopService::addNewEmployee(const Employee& employee,
                                                      const EmployeeAssignment& employee_assignment) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->uploadEmployee(employee, employee_assignment);
}

std::optional<Employee> domain::ShopService::getEmployee(const EmployeeId& employee_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->downloadEmployee(employee_id);
}

std::optional<EmployeeAssignment> domain::ShopService::getEmployeeAssignment(const EmployeeId& employee_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->downloadEmployeeAssignment(employee_id);
}

std::optional<EmployeeAssignments> domain::ShopService::getDepartmentAssignments(
    const DepartmentId& department_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->downloadDepartmentAssignments(department_id);
}

bool domain::ShopService::removeEmployee(const EmployeeId& employee_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->removeEmployee(employee_id);
}

std::optional<Departments> domain::ShopService::getDepartments() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->downloadDepartments();
}

std::optional<StaffPositions> domain::ShopService::getStaffPositions() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->downloadStaffPositions();
}

bool domain::ShopService::updateEmployee(const EmployeeId& employee_id,
                                         const Employee& employee,
                                         const EmployeeAssignment& employee_assignment) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    if (shop_repository_->updateEmployee(employee_id, employee) &&
        shop_repository_->updateEmployeeAssignment(employee_id, employee_assignment)) {
        return true;
    }

    return false;
}
