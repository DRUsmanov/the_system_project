#include "timesheet_service_factory_impl.h"

#include "logger.h"
#include "repositories_impl/timesheet_repository/timesheet_repository.h"
#include "services/timesheet_service/timesheet_service.h"

using namespace infrastructure;

std::shared_ptr<application::TimesheetServiceInterface> TimesheetServiceFactory::createTimesheetService(
    std::shared_ptr<application::UowInterface> uow) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto timesheet_repository = std::make_shared<TimesheetRepository>(std::dynamic_pointer_cast<Uow>(uow));
    return std::make_shared<application::TimesheetService>(timesheet_repository);
}