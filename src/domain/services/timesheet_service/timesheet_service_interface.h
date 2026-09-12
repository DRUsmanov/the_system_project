#pragma once

#include <chrono>
#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments.h"
#include "entities/timesheet/timesheet.h"

namespace domain {

class TimesheetServiceInterface {
public:
    virtual ~TimesheetServiceInterface() = default;

    virtual std::optional<Timesheet> getDepartmentTimesheet(DepartmentId department_id,
                                                            AdminCategoryId admin_category_id,
                                                            std::chrono::year_month year_month) const = 0;
    virtual bool generateTimesheetForAllEmployees(const EmployeeAssignments& employee_assignments,
                                                  std::chrono::year year) = 0;
    virtual bool generateTimesheetForNewEmployee(const EmployeeAssignment& employee_assignment,
                                                 const Employee& employee) = 0;
    virtual std::optional<WorkSchedules> getWorkSchedules() const = 0;
};

}  // namespace domain
