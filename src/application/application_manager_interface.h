#pragma once

#include "application/services/timesheet_service/timesheet_service_interface.h"
#include "application/services/shop_service/shop_service_interface.h"
#include "application/dto/login_dto.h"
#include "application/dto/timesheet_dto.h"

#include <chrono>
#include <optional>

namespace application{

class ApplicationManagerInterface{
public:
    ApplicationManagerInterface(
        TimesheetServiceInterface& timesheet_service
        , ShopServiceInterface& shop_service
    )
    : timesheet_service_{timesheet_service}
    , shop_service_{shop_service} { }

    virtual ~ApplicationManagerInterface() = default;

    virtual std::optional<OutputTimesheetDto> GetTimesheet(const InputTimesheetDto& input_timesheet_dto) const = 0;
    virtual std::optional<OutputLoginDto> GetUser(const InputLoginDto& input_login_dto) const = 0;
protected:
    TimesheetServiceInterface& timesheet_service_;
    ShopServiceInterface& shop_service_;
};
    
} // namespace application
