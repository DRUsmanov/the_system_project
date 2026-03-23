#pragma once

#include "domain/entities/timesheet/timesheet.h"
#include "domain/interfaces/repositorys/timesheet_repository_interface.h"

#include <chrono>

namespace application{

class TimeSheetServiceInterface{
public:
    TimeSheetServiceInterface(domain::TimeSheetRepositoryInterface& timesheet_repository)
    : timesheet_repository_{timesheet_repository} { }

    virtual ~TimeSheetServiceInterface() = default;

    virtual domain::Timesheet GetTimesheet(domain::DepartmentId department_id, domain::AdministratorId administrator_id
                                    , std::chrono::year_month year_month) const = 0;
    virtual domain::Timesheet GenerateTimeSheet(const domain::Shop& shop, std::chrono::year year) = 0;
protected:
    domain::TimeSheetRepositoryInterface& timesheet_repository_;
};

} // namespace application

