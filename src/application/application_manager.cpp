#include "application_manager.h"

#include <exception>

using namespace application;

std::optional<UserIdOutputDto> ApplicationManager::Login(const UserLoginInputDto &user_login_input_dto) const {
    try {
        domain::UserLoginData user_login_data = user_dto_mapper_.Convert(user_login_input_dto);
        std::shared_ptr<application::UowInterface> uow = uow_factory_.CreateUow();
        std::shared_ptr<application::UserServiceInterface> user_service = user_service_factory_.CreateUserService(uow);

        std::optional<domain::User> user = user_service->Login(user_login_data);

        if (!user.has_value()){
            return std::nullopt;
        }
        
        UserIdOutputDto user_id_output_dto = user_dto_mapper_.Convert(*user);
        return user_id_output_dto;
    }
    catch (std::exception& ex){
        return std::nullopt;
    }
}

std::optional<application::TimesheetOutputDto> application::ApplicationManager::GetTimesheet(const application::TimesheetInputDto &input_timesheet_dto) const
{
    try {
        domain::DepartmentId department_id{input_timesheet_dto.department_id};
        domain::AdminCategoryId admin_category_id{input_timesheet_dto.admin_category_id};
        std::chrono::year year{input_timesheet_dto.year};
        std::chrono::month month{input_timesheet_dto.month};
        std::chrono::year_month year_month = year / month;

        auto uow = uow_factory_.CreateUow();
        auto timesheet_service = timesheet_service_factory_.CreateTimesheetService(uow);
        auto shop_service = shop_service_factory_.CreateShopService(uow);

        auto timesheet = timesheet_service->GetTimesheet(department_id, admin_category_id, year_month);
        if (!timesheet.has_value()) {
            auto shop = shop_service->GetShop();
            timesheet_service->GenerateTimesheet(shop, year_month.year());
        }
        timesheet = timesheet_service->GetTimesheet(department_id, admin_category_id, year_month);
        // return timesheet;
    }
    catch (std::exception& ex){
        return std::nullopt;
    }
}