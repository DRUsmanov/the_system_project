#pragma once

#include "factories/timesheet_service_factory_interface.h"

namespace infrastructure {

class TimesheetServiceFactory : public domain::TimesheetServiceFactoryInterface {
public:
    std::shared_ptr<domain::TimesheetServiceInterface> createTimesheetService(
        std::shared_ptr<domain::UowInterface> uow) const override;
};

}  // namespace infrastructure