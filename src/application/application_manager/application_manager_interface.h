#pragma once

#include <chrono>
#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/shop.h"
#include "entities/timesheet/timesheet.h"
#include "entities/user/user.h"
namespace application {

class ApplicationManagerInterface {
public:
    virtual ~ApplicationManagerInterface() = default;

    virtual std::optional<domain::User> login(std::string login, std::string password) const = 0;

    virtual bool addEmployee(const domain::UserId& user_id,
                             const domain::Shop::EmployeeAssignment& employee_assignment,
                             const domain::Employee& employee) const = 0;

    virtual std::optional<domain::Timesheet> getTimesheet(const domain::UserId& user_id,
                                                          const domain::AdminCategoryId& admin_category_id,
                                                          const domain::DepartmentId& department_id,
                                                          std::chrono::year_month year_month) const = 0;
};

}  // namespace application
