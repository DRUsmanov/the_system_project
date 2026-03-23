#include "application_manager.h"

#include <exception>

domain::Timesheet application::ApplicationManager::GetTimesheet(domain::DepartmentId department_id, domain::AdministratorId administrator_id
                                                                , std::chrono::year_month year_month) const {
    auto timesheet = timesheet_service_.GetTimesheet(department_id, administrator_id, year_month);
    if (timesheet.IsEmpty()){
        auto shop = shop_service_.GetShop();
        timesheet = timesheet_service_.GenerateTimeSheet(shop, year_month.year());
        auto timesheet = timesheet_service_.GetTimesheet(department_id, administrator_id, year_month);
    }
    return timesheet;
}