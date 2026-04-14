#pragma once

#include "domain/entities/timesheet/timesheet.h"
#include "domain/interfaces/repositorys/timesheet_repository_interface.h"

#include <chrono>
#include <optional>

namespace application{

class TimesheetServiceInterface {
public:
    virtual ~TimesheetServiceInterface() = default;

    virtual std::optional<domain::Timesheet> GetTimesheet(domain::DepartmentId department_id, domain::AdminCategoryId admin_category_id
                                                            , std::chrono::year_month year_month) const = 0;
    virtual domain::Timesheet GenerateTimesheet(const domain::Shop& shop, std::chrono::year year) = 0;
    virtual bool AddTimesheet(const domain::Timesheet& timesheet) = 0;
};

} // namespace application

