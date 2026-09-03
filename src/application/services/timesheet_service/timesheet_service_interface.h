#pragma once

#include <chrono>
#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/shop.h"
#include "entities/timesheet/timesheet.h"

namespace application {

class TimesheetServiceInterface {
public:
    virtual ~TimesheetServiceInterface() = default;

    virtual std::optional<domain::Timesheet> getDepartmentTimesheet(domain::DepartmentId department_id,
                                                                    domain::AdminCategoryId admin_category_id,
                                                                    std::chrono::year_month year_month) const = 0;
    virtual bool generateTimesheetForShop(const domain::Shop& shop, std::chrono::year year) = 0;
    virtual bool generateTimesheetForNewEmployee(const domain::Shop::EmployeeAssignment& employee_assignment,
                                                 const domain::Employee& employee) = 0;
};

}  // namespace application
