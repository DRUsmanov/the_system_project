#include "application_manager.h"

domain::Timesheet application::ApplicationManager::GetTimesheet(domain::DepartmentId department_id, std::chrono::year_month year_month
                                                                , domain::AdministratorId administrator_id) const {
    auto timesheet = timesheet_service_.GetTimesheet(department_id, year_month);
    if (timesheet.IsEmpty()){
        
    }
}