#pragma once

#include "application/services/timesheet_service/timesheet_service.h"
#include "application/services/shop_service/shop_service.h"
#include "domain/entities/timesheet/timesheet.h"

#include <chrono>

namespace application{

class ApplicationManager{
public:
    ApplicationManager(
        TimeSheetService& timesheet_service
        , ShopService shop_service
    )
    : timesheet_service_{timesheet_service}
    , shop_service_{shop_service} { }

    domain::Timesheet GetTimesheet(domain::DepartmentId department_id, std::chrono::year_month year_month
                                    , domain::AdministratorId administrator_id) const;
private:
    TimeSheetService& timesheet_service_;
    ShopService& shop_service_;
};
    
} // namespace application
