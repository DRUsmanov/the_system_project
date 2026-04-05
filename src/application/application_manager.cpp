#include "application_manager.h"

#include <exception>

std::optional<application::OutputTimesheetDto> application::ApplicationManager::GetTimesheet(const application::InputTimesheetDto& input_timesheet_dto) const {
    try {
        domain::DepartmentId department_id{input_timesheet_dto.department_id};
        domain::AdministratorId administrator_id{input_timesheet_dto.administrator_id};
        std::chrono::year year{input_timesheet_dto.year};
        std::chrono::month month{input_timesheet_dto.month};
        std::chrono::year_month year_month = year / month;
        auto timesheet = timesheet_service_.GetTimesheet(department_id, administrator_id, year_month);
        if (!timesheet.has_value()) {
            auto shop = shop_service_.GetShop();
            timesheet_service_.GenerateTimesheet(shop, year_month.year());
        }
        timesheet = timesheet_service_.GetTimesheet(department_id, administrator_id, year_month);
        return timesheet;
    }
    catch (std::exception& ex){
        return std::nullopt;
    }
}