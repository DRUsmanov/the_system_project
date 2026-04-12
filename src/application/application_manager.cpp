#include "application_manager.h"

#include <exception>

std::optional<application::OutputTimesheetDto> application::ApplicationManager::GetTimesheet(const application::InputTimesheetDto& input_timesheet_dto) const {
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