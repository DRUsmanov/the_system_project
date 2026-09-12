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

std::optional<domain::EmployeeId> ApplicationManager::addEmployee(const domain::UserId& user_id,
                                                                  const domain::EmployeeAssignment& employee_assignment,
                                                                  domain::Employee& employee) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto timesheet_service = timesheet_service_factory_.createTimesheetService(uow);
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

        if (!permission_service->checkUserDepartmentWritePermission(user_id, employee_assignment.department_id)) {
            return std::nullopt;
        }

        auto employee_id = shop_service->addNewEmployee(employee_assignment, employee);

        if (!employee_id) {
            return std::nullopt;
        }

        employee.employee_id = employee_id.value();

        if (!timesheet_service->generateTimesheetForNewEmployee(employee_assignment, employee)) {
            return std::nullopt;
        }

        uow->commit();

        return employee_id;
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}

bool ApplicationManager::removeEmployee(const domain::UserId& user_id, domain::EmployeeId employee_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    try {
        auto uow = uow_factory_.createUow();
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

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

std::optional<domain::Timesheet> ApplicationManager::getTimesheet(const domain::UserId& user_id,
                                                                  const domain::AdminCategoryId& admin_category_id,
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

        std::optional<domain::Timesheet> timesheet =
            timesheet_service->getDepartmentTimesheet(department_id, admin_category_id, year_month);

        if (timesheet.has_value()) {
            return timesheet;
        }

        domain::EmployeeAssignments employee_assignments = shop_service->getAllEmployeeAssignments();
        timesheet_service->generateTimesheetForAllEmployees(employee_assignments, year_month.year());
        return timesheet_service->getDepartmentTimesheet(department_id, admin_category_id, year_month);
    } catch (std::exception& ex) {
        utils::logException(ex);
        return std::nullopt;
    }
}