#include "application_manager/application_manager.h"

#include <exception>
#include <iostream>

#include "logger.h"

using namespace application;

std::optional<domain::User> ApplicationManager::login(std::string login, std::string password) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto user_service = user_service_factory_.createUserService(uow);

        return user_service->login(login, password);
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

std::optional<domain::EmployeeId> ApplicationManager::addEmployee(
    const domain::UserId& user_id,
    const domain::Employee& employee,
    const domain::EmployeeAssignment& employee_assignment) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto timesheet_service = timesheet_service_factory_.createTimesheetService(uow);
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

        if (!permission_service->checkUserDepartmentWritePermission(user_id, employee_assignment.department_id)) {
            return std::nullopt;
        }

        auto employee_id = shop_service->addNewEmployee(employee, employee_assignment);

        if (!employee_id) {
            return std::nullopt;
        }

        if (!timesheet_service->generateTimesheetForNewEmployee(employee_id.value(), employee, employee_assignment)) {
            return std::nullopt;
        }

        uow->commit();

        return employee_id;
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

bool ApplicationManager::removeEmployee(const domain::UserId& user_id,
                                        domain::EmployeeId employee_id,
                                        const domain::Date& removing_date) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);
        auto timesheet_service = timesheet_service_factory_.createTimesheetService(uow);

        auto employee_assignment = shop_service->getEmployeeAssignment(employee_id);

        if (!employee_assignment.has_value()) {
            return false;
        }

        if (!permission_service->checkUserDepartmentWritePermission(user_id,
                                                                    employee_assignment.value().department_id)) {
            return false;
        }

        if (!shop_service->removeEmployee(employee_id)) {
            return false;
        }

        if (!timesheet_service->removeTimesheetForEmployeeFromDate(employee_id, removing_date)) {
            return false;
        }

        uow->commit();

        return true;
    } catch (std::exception& ex) {
        utils::logException(ex);
        return false;
    }
}

std::optional<domain::Employee> ApplicationManager::getEmployee(const domain::UserId& user_id,
                                                                const domain::EmployeeId& employee_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

        auto employee_assignment = shop_service->getEmployeeAssignment(employee_id);

        if (!employee_assignment.has_value()) {
            return std::nullopt;
        }

        if (!permission_service->checkUserDepartmentReadPermission(user_id,
                                                                   employee_assignment.value().department_id)) {
            return std::nullopt;
        }

        return shop_service->getEmployee(employee_id);
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

std::optional<domain::Departments> application::ApplicationManager::getDepartments(
    [[maybe_unused]] const domain::UserId& user_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto shop_service = shop_service_factory_.createShopService(uow);

        return shop_service->getDepartments();
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

std::optional<domain::StaffPositions> ApplicationManager::getStaffPositions(
    [[maybe_unused]] const domain::UserId& user_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto shop_service = shop_service_factory_.createShopService(uow);

        return shop_service->getStaffPositions();
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

std::optional<domain::WorkSchedules> ApplicationManager::getWorkSchedules(
    [[maybe_unused]] const domain::UserId& user_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto timesheet_service = timesheet_service_factory_.createTimesheetService(uow);

        return timesheet_service->getWorkSchedules();
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

std::optional<domain::Staff> ApplicationManager::getDepartmentStaff(const domain::UserId& user_id,
                                                                    const domain::DepartmentId department_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

        if (!permission_service->checkUserDepartmentReadPermission(user_id, department_id)) {
            return std::nullopt;
        }

        auto department_employee_assignments = shop_service->getDepartmentAssignments(department_id);

        if (!department_employee_assignments.has_value()) {
            return std::nullopt;
        }

        domain::Staff department_staff{std::move(department_employee_assignments.value())};

        const auto& employee_assignments = department_staff.getEmployeeAssignments();

        for (const auto& [employee_id, employee_assignment] : employee_assignments) {
            auto employee = shop_service->getEmployee(employee_id);

            if (!employee.has_value()) {
                return std::nullopt;
            }

            department_staff.addEmployee(employee_id, employee.value());
        }

        return department_staff;

    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

bool application::ApplicationManager::updateEmployee(
    const domain::UserId& user_id,
    const domain::EmployeeId& employee_id,
    const domain::Employee& employee,
    const domain::EmployeeAssignment& employee_assignment,
    const std::optional<domain::Date>& assignment_changing_date) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

        if (!permission_service->checkUserDepartmentWritePermission(user_id, employee_assignment.department_id)) {
            return false;
        }

        if (!shop_service->updateEmployee(employee_id, employee, employee_assignment)) {
            return false;
        }

        if (assignment_changing_date.has_value()) {
            if (assignment_changing_date < employee.employment_date) {
                return false;
            }
            auto timesheet_service = timesheet_service_factory_.createTimesheetService(uow);
            if (!timesheet_service->updateTimesheetForEmployee(employee_id,
                                                               employee_assignment,
                                                               assignment_changing_date.value())) {
                return false;
            }
        }

        uow->commit();

        return true;

    } catch (std::exception& ex) {
        utils::logException(ex);
        return false;
    }
}

std::optional<domain::Timesheet> ApplicationManager::getTimesheet(const domain::UserId& user_id,
                                                                  const domain::DepartmentId& department_id,
                                                                  std::chrono::year_month year_month) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto timesheet_service = timesheet_service_factory_.createTimesheetService(uow);
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto user_service = user_service_factory_.createUserService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

        if (!permission_service->checkUserDepartmentReadPermission(user_id, department_id)) {
            return std::nullopt;
        }

        auto user = user_service->getUser(user_id);

        if (!user.has_value()) {
            return std::nullopt;
        }

        std::optional<domain::Timesheet> timesheet =
            timesheet_service->getDepartmentTimesheet(department_id, user->admin_category_id, year_month);

        if (timesheet.has_value()) {
            return timesheet;
        }

        domain::EmployeeAssignments employee_assignments = shop_service->getAllEmployeeAssignments();
        timesheet_service->generateTimesheetForAllEmployees(employee_assignments, year_month.year());
        return timesheet_service->getDepartmentTimesheet(department_id, user->admin_category_id, year_month);
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}