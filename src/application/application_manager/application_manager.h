#pragma once

#include <chrono>

#include "application_manager/application_manager_interface.h"
#include "factories/permission_service_factory_interface.h"
#include "factories/shop_service_factory_interface.h"
#include "factories/timesheet_service_factory_interface.h"
#include "factories/uow_factory_interface.h"
#include "factories/user_service_factory_interface.h"

namespace application {

class ApplicationManager : public ApplicationManagerInterface {
public:
    ApplicationManager(const domain::UowFactoryInterface& uow_factory,
                       const domain::PermissionServiceFactoryInterface& permission_service_factory,
                       const domain::UserServiceFactoryInterface& user_service_factory,
                       const domain::TimesheetServiceFactoryInterface& timesheet_service_factory,
                       const domain::ShopServiceFactoryInterface& shop_service_factory) :
        uow_factory_{uow_factory}, permission_service_factory_{permission_service_factory},
        user_service_factory_{user_service_factory}, timesheet_service_factory_{timesheet_service_factory},
        shop_service_factory_{shop_service_factory} {}

    std::optional<domain::User> login(std::string login, std::string password) const override;

    std::optional<domain::EmployeeId> addEmployee(const domain::UserId& user_id,
                                                  const domain::Employee& employee,
                                                  const domain::EmployeeAssignment& employee_assignment) const override;
    bool removeEmployee(const domain::UserId& user_id,
                        domain::EmployeeId employee_id,
                        const domain::Date& removing_date) const override;
    std::optional<domain::Employee> getEmployee(const domain::UserId& user_id,
                                                const domain::EmployeeId& employee_id) const override;
    std::optional<domain::Departments> getDepartments(const domain::UserId& user_id) const override;
    std::optional<domain::StaffPositions> getStaffPositions(const domain::UserId& user_id) const override;
    std::optional<domain::WorkSchedules> getWorkSchedules(const domain::UserId& user_id) const override;
    std::optional<domain::Staff> getDepartmentStaff(const domain::UserId& user_id,
                                                    const domain::DepartmentId department_id) const override;
    bool updateEmployee(const domain::UserId& user_id,
                        const domain::EmployeeId& employee_id,
                        const domain::Employee& employee,
                        const domain::EmployeeAssignment& employee_assignment,
                        const std::optional<domain::Date>& assignment_changing_date) const override;
    std::optional<domain::Timesheet> getDepartmentTimesheet(const domain::UserId& user_id,
                                                            const domain::DepartmentId& department_id,
                                                            std::chrono::year_month year_month) const override;

private:
    const domain::UowFactoryInterface& uow_factory_;
    const domain::PermissionServiceFactoryInterface& permission_service_factory_;
    const domain::UserServiceFactoryInterface& user_service_factory_;
    const domain::TimesheetServiceFactoryInterface& timesheet_service_factory_;
    const domain::ShopServiceFactoryInterface& shop_service_factory_;
};

}  // namespace application
