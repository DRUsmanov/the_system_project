#include "timesheet_service_factory_impl.h"

#include "infrastructure/repositorys_impl/timesheet_repository/"

using namespace infrastructure;

std::shared_ptr<application::TimesheetServiceInterface> TimesheetServiceFactory::createTimesheetService(
    std::shared_ptr<application::UowInterface> uow) const {
    return std::shared_ptr<application::TimesheetServiceInterface>();
}