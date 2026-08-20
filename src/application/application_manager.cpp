#include "application_manager.h"

#include <exception>

using namespace application;

std::optional<domain::User> ApplicationManager::login(std::string login, std::string password) const {
    try {
        std::shared_ptr<application::UowInterface> uow = uow_factory_.createUow();
        std::shared_ptr<application::UserServiceInterface> user_service = user_service_factory_.createUserService(uow);

        return user_service->login(login, password);
    } catch (std::exception& ex) {
        return std::nullopt;
    }
}

bool ApplicationManager::addNewEmployee(const domain::UserId& user_id,
                                        const domain::Shop::EmployeeAssignment& employee_assignment,
                                        const domain::Employee& employee) const {
    try {
        std::shared_ptr<application::UowInterface> uow = uow_factory_.createUow();
        std::shared_ptr<application::TimesheetServiceInterface> timesheet_service =
            timesheet_service_factory_.createTimesheetService(uow);
        std::shared_ptr<application::ShopServiceInterface> shop_service = shop_service_factory_.createShopService(uow);
        std::shared_ptr<application::UserServiceInterface> user_service = user_service_factory_.createUserService(uow);
        std::shared_ptr<application::PermissionServiceInterface> permission_service =
            permission_service_factory_.createPermissionService(uow);

        std::optional<domain::User> user = user_service->getUser(user_id);

        if (!permission_service->checkUserAddEmployeeToDepartmentPermission(user_id,
                                                                            employee_assignment.department_id)) {
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
        std::shared_ptr<application::UowInterface> uow = uow_factory_.createUow();
        std::shared_ptr<application::TimesheetServiceInterface> timesheet_service =
            timesheet_service_factory_.createTimesheetService(uow);
        std::shared_ptr<application::ShopServiceInterface> shop_service = shop_service_factory_.createShopService(uow);
        std::optional<domain::Timesheet> timesheet =
            timesheet_service->getDepartmentTimesheet(department_id, admin_category_id, year_month);

        if (!timesheet.has_value()) {
            domain::Shop shop = shop_service->getShop();
            timesheet_service->generateTimesheetForShop(shop, year_month.year());
        }

        return timesheet_service->getDepartmentTimesheet(department_id, admin_category_id, year_month);
    } catch (std::exception& ex) {
        return std::nullopt;
    }
}