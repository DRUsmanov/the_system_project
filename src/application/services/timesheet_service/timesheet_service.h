#pragma once

#include "domain/entities/shop/shop.h"
#include "domain/interfaces/repositorys/timesheet_repository.h"

#include <chrono>

namespace application{

class TimeSheetService{
public:
    TimeSheetService(domain::TimeSheetRepositoryInterface& timesheet_repository)
    : timesheet_repository_{timesheet_repository} { }

    domain::Timesheet GetTimesheet(domain::DepartmentId department_id, std::chrono::year_month year_month) const;
private:
    domain::TimeSheetRepositoryInterface& timesheet_repository_;

    domain::Timesheet GenerateTimeSheet(const domain::Shop& shop, std::chrono::year year);
};

} // namespace application

