#pragma once

#include "application/services/timesheet_service/timesheet_service_interface.h"
#include "application/uow/uow_interface.h"

#include <memory>

namespace application {

class TimesheetServiceFactoryInterface {
public:
    virtual ~TimesheetServiceFactoryInterface() = default;

    virtual std::shared_ptr<TimesheetServiceInterface> CreateTimesheetService(std::shared_ptr<UowInterface> uow) const = 0;
};
    
} // namespace application


