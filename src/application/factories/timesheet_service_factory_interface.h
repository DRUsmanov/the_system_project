#pragma once

#include <memory>

#include "application/services/timesheet_service/timesheet_service_interface.h"
#include "application/uow/uow_interface.h"

namespace application {

class TimesheetServiceFactoryInterface {
public:
    virtual ~TimesheetServiceFactoryInterface() = default;

    virtual std::shared_ptr<TimesheetServiceInterface> createTimesheetService(
        std::shared_ptr<UowInterface> uow) const = 0;
};

}  // namespace application
