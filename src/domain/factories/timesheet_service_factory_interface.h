#pragma once

#include <memory>

#include "services/timesheet_service/timesheet_service_interface.h"
#include "uow/uow_interface.h"

namespace domain {

class TimesheetServiceFactoryInterface {
public:
    virtual ~TimesheetServiceFactoryInterface() = default;

    virtual std::shared_ptr<TimesheetServiceInterface> createTimesheetService(
        std::shared_ptr<UowInterface> uow) const = 0;
};

}  // namespace domain
