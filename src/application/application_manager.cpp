#include "application_manager.h"

#include <exception>

std::optional<domain::Timesheet> application::ApplicationManager::GetTimesheet(domain::DepartmentId department_id, domain::AdministratorId administrator_id
                                                                                , std::chrono::year_month year_month) const {
    try {
        auto timesheet = timesheet_service_.GetTimesheet(department_id, administrator_id, year_month);
        if (!timesheet.has_value()) {
            auto shop = shop_service_.GetShop();
            timesheet_service_.GenerateTimesheet(shop, year_month.year());
        }
        return timesheet;
    }
    catch (std::exception& ex){
        return std::nullopt;
    }
}