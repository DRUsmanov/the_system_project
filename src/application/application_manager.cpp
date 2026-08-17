#include "application_manager.h"

#include <exception>

using namespace application;

std::optional<UserIdOutputDto> ApplicationManager::login(const UserLoginInputDto& user_login_input_dto) const {
    try {
        domain::UserLoginData user_login_data = user_dto_mapper_.convert(user_login_input_dto);
        std::shared_ptr<application::UowInterface> uow = uow_factory_.createUow();
        std::shared_ptr<application::UserServiceInterface> user_service = user_service_factory_.createUserService(uow);

        std::optional<domain::User> user = user_service->login(user_login_data);

        if (!user.has_value()) {
            return std::nullopt;
        }

        UserIdOutputDto user_id_output_dto = user_dto_mapper_.convert(*user);
        return user_id_output_dto;
    } catch (std::exception& ex) {
        return std::nullopt;
    }
}

bool ApplicationManager::addEmployee(const UserIdInputDto& user_id_input_dto,
                                     const AddEmployeeInputDto& add_employee_input_dto) const {
    try {
        std::pair<domain::DepartmentId, domain::Employee> department_id_with_employee =
            shop_dto_mapper_.convert(add_employee_input_dto);
        domain::UserId user_id = user_dto_mapper_.convert(user_id_input_dto);

        std::shared_ptr<application::UowInterface> uow = uow_factory_.createUow();
        std::shared_ptr<application::TimesheetServiceInterface> timesheet_service =
            timesheet_service_factory_.createTimesheetService(uow);
        std::shared_ptr<application::ShopServiceInterface> shop_service = shop_service_factory_.createShopService(uow);
        std::shared_ptr<application::UserServiceInterface> user_service = user_service_factory_.createUserService(uow);
        std::shared_ptr<application::PermissionServiceInterface> permission_service =
            permission_service_factory_.createPermissionService(uow);

        std::optional<domain::User> user = user_service->getUser(user_id);

        if (!user.has_value()) {
            return false;
        }

        if (!permission_service->checkUserAddEmployeePermission(user->user_id, department_id_with_employee.first)) {
            return false;
        }

        shop_service->addEmployee(department_id_with_employee.second, );
        // TODO: сгенерировать табель для работника

    } catch (std::exception& ex) {
        return false;
    }
}

std::optional<application::TimesheetOutputDto> application::ApplicationManager::getTimesheet(
    const application::TimesheetInputDto& input_timesheet_dto) const {
    try {
        domain::DepartmentId department_id{input_timesheet_dto.department_id};
        domain::AdminCategoryId admin_category_id{input_timesheet_dto.admin_category_id};
        std::chrono::year year{input_timesheet_dto.year};
        std::chrono::month month{input_timesheet_dto.month};
        std::chrono::year_month year_month = year / month;

        std::shared_ptr<application::UowInterface> uow = uow_factory_.createUow();
        std::shared_ptr<application::TimesheetServiceInterface> timesheet_service =
            timesheet_service_factory_.createTimesheetService(uow);
        std::shared_ptr<application::ShopServiceInterface> shop_service = shop_service_factory_.createShopService(uow);

        std::optional<domain::Timesheet> timesheet =
            timesheet_service->getTimesheet(department_id, admin_category_id, year_month);
        if (!timesheet.has_value()) {
            domain::Shop shop = shop_service->getShop();
            timesheet_service->generateTimesheetForShop(shop, year_month.year());
        }
        timesheet = timesheet_service->getTimesheet(department_id, admin_category_id, year_month);
        if (!timesheet.has_value()) {
            return std::nullopt;
        }
        // mapping timesheet in DTO and return
    } catch (std::exception& ex) {
        return std::nullopt;
    }
}