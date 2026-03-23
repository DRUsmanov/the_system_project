#pragma once

#include "application/services/timesheet_service/timesheet_service_interface.h"
#include "application/services/shop_service/shop_service_interface.h"
#include "domain/entities/timesheet/timesheet.h"

#include <chrono>

namespace application{

class ApplicationManagerInterface{
public:
    ApplicationManagerInterface(
        TimeSheetServiceInterface& timesheet_service
        , ShopServiceInterface& shop_service
    )
    : timesheet_service_{timesheet_service}
    , shop_service_{shop_service} { }

    virtual ~ApplicationManagerInterface() = default;

    virtual domain::Timesheet GetTimesheet(domain::DepartmentId department_id, domain::AdministratorId administrator_id
                                    , std::chrono::year_month year_month) const = 0;
protected:
    TimeSheetServiceInterface& timesheet_service_;
    ShopServiceInterface& shop_service_;
};
    
} // namespace application
