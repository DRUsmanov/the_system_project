#pragma once

#include "factories/timesheet_service_factory_interface.h"

namespace infrastructure {

class TimesheetServiceFactory : public application::TimesheetServiceFactoryInterface {
public:
    std::shared_ptr<application::TimesheetServiceInterface> createTimesheetService(
        std::shared_ptr<application::UowInterface> uow) const override;
};

}  // namespace infrastructure