#include "application_manager.h"

#include <exception>

using namespace application;

std::optional<domain::User> ApplicationManager::login(std::string login, std::string password) const {
    try {
        auto uow = uow_factory_.createUow();
        auto user_service = user_service_factory_.createUserService(uow);

        return user_service->login(login, password);
    } catch (std::exception& ex) {
        return std::nullopt;
    }
}

bool ApplicationManager::addEmployee(const domain::UserId& user_id,
                                     const domain::Shop::EmployeeAssignment& employee_assignment,
                                     const domain::Employee& employee) const {
    try {
        auto uow = uow_factory_.createUow();
        auto timesheet_service = timesheet_service_factory_.createTimesheetService(uow);
        auto shop_service = shop_service_factory_.createShopService(uow);
        auto permission_service = permission_service_factory_.createPermissionService(uow);

        if (!permission_service->checkUserDepartmentWritePermission(user_id, employee_assignment.department_id)) {
            return false;
        }

        if (!shop_service->addNewEmployee(employee_assignment, employee)) {
            return false;
        }

        if (!timesheet_service->generateTimesheetForNewEmployee(employee_assignment, employee)) {
            return false;
        }

        uow->commit();

        return true;
    } catch (std::exception& ex) {
        return false;
    }
}

std::optional<domain::Timesheet> ApplicationManager::getTimesheet(const domain::UserId& user_id,
                                                                  const domain::AdminCategoryId& admin_category_id,
                                                                  const domain::DepartmentId& department_id,
                                                                  std::chrono::year_month year_month) const {
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

        domain::Shop shop = shop_service->getShop();
        timesheet_service->generateTimesheetForShop(shop, year_month.year());
        return timesheet_service->getDepartmentTimesheet(department_id, admin_category_id, year_month);
    } catch (std::exception& ex) {
        return std::nullopt;
    }
}