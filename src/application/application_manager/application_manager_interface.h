#pragma once

#include <chrono>
#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments/employee_assignments.h"
#include "entities/shop/staff/staff.h"
#include "entities/timesheet/timesheet.h"
#include "entities/timesheet/work_schedules/work_schedule.h"
#include "entities/user/user.h"
namespace application {

class ApplicationManagerInterface {
public:
    virtual ~ApplicationManagerInterface() = default;

    virtual std::optional<domain::User> login(std::string login, std::string password) const = 0;
    virtual std::optional<domain::EmployeeId> addEmployee(
        const domain::UserId& user_id,
        const domain::Employee& employee,
        const domain::EmployeeAssignment& employee_assignment) const = 0;
    virtual bool removeEmployee(const domain::UserId& user_id,
                                domain::EmployeeId employee_id,
                                const domain::Date& removing_date) const = 0;
    virtual std::optional<domain::Employee> getEmployee(const domain::UserId& user_id,
                                                        const domain::EmployeeId& employee_id) const = 0;
    virtual std::optional<domain::Departments> getDepartments(const domain::UserId& user_id) const = 0;
    virtual std::optional<domain::StaffPositions> getStaffPositions(const domain::UserId& user_id) const = 0;
    virtual std::optional<domain::WorkSchedules> getWorkSchedules(const domain::UserId& user_id) const = 0;
    virtual std::optional<domain::Staff> getDepartmentStaff(const domain::UserId& user_id,
                                                            const domain::DepartmentId department_id) const = 0;
    virtual bool updateEmployee(const domain::UserId& user_id,
                                const domain::EmployeeId& employee_id,
                                const domain::Employee& employee,
                                const domain::EmployeeAssignment& employee_assignment,
                                const std::optional<domain::Date>& assignment_changing_date) const = 0;
    virtual std::optional<domain::Timesheet> getDepartmentTimesheet(const domain::UserId& user_id,
                                                                    const domain::DepartmentId& department_id,
                                                                    std::chrono::year_month year_month) const = 0;
    virtual const domain::LeaveTypeDescriptions& getLeaveTypeDescriptions(const domain::UserId& user_id) const = 0;
};

}  // namespace application
