#include "timesheet_service_factory_impl.h"

#include "repositories_impl/timesheet_repository/timesheet_repository.h"

using namespace infrastructure;

std::shared_ptr<application::TimesheetServiceInterface> TimesheetServiceFactory::createTimesheetService(
    std::shared_ptr<application::UowInterface> uow) const {
    return std::shared_ptr<application::TimesheetServiceInterface>();
}