#pragma once

#include "application_manager_interface.h"

#include <chrono>

namespace application{

class ApplicationManager : public ApplicationManagerInterface {
public:
    ApplicationManager(
        TimeSheetServiceInterface& timesheet_service
        , ShopServiceInterface& shop_service
    )
    : ApplicationManagerInterface{timesheet_service, shop_service} { }

    domain::Timesheet GetTimesheet(domain::DepartmentId department_id, domain::AdministratorId administrator_id
                                    , std::chrono::year_month year_month) const override;
};
    
} // namespace application
