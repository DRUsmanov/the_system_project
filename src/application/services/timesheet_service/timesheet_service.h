#pragma once

#include "timesheet_service_interface.h"

#include <chrono>

namespace application{

class TimeSheetService : public TimeSheetServiceInterface{
public:
    TimeSheetService(domain::TimeSheetRepositoryInterface& timesheet_repository)
    : TimeSheetServiceInterface{timesheet_repository} { }

    domain::Timesheet GetTimesheet(domain::DepartmentId department_id, domain::AdministratorId administrator_id
                                    , std::chrono::year_month year_month) const override;
    domain::Timesheet GenerateTimeSheet(const domain::Shop& shop, std::chrono::year year) override;
};

} // namespace application

