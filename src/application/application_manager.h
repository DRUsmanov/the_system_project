#pragma once

#include "application_manager_interface.h"

#include <chrono>

namespace application{

class ApplicationManager : public ApplicationManagerInterface {
public:
    ApplicationManager(
        TimesheetServiceInterface& timesheet_service
        , ShopServiceInterface& shop_service
    )
    : ApplicationManagerInterface{timesheet_service, shop_service} { }

    std::optional<OutputTimesheetDto> GetTimesheet(const InputTimesheetDto& input_timesheet_dto) const override;
};
    
} // namespace application
