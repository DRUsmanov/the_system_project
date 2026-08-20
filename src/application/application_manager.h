#pragma once

#include <chrono>

#include "application/factorys/permission_service_factory_interface.h"
#include "application/factorys/shop_service_factory_interface.h"
#include "application/factorys/timesheet_service_factory_interface.h"
#include "application/factorys/uow_factory_interface.h"
#include "application/factorys/user_service_factory_interface.h"
#include "application_manager_interface.h"

namespace application {

class ApplicationManager : public ApplicationManagerInterface {
public:
    ApplicationManager(const UowFactoryInterface& uow_factory,
                       const PermissionServiceFactoryInterface& permission_service_factory,
                       const UserServiceFactoryInterface& user_service_factory,
                       const TimesheetServiceFactoryInterface& timesheet_service_factory,
                       const ShopServiceFactoryInterface& shop_service_factory) :
        uow_factory_{uow_factory}, permission_service_factory_{permission_service_factory},
        user_service_factory_{user_service_factory}, timesheet_service_factory_{timesheet_service_factory},
        shop_service_factory_{shop_service_factory} {}

    std::optional<domain::User> login(std::string login, std::string password) const override;

    bool addNewEmployee(const domain::UserId& user_id,
                        const domain::Shop::EmployeeAssignment& employee_assignment,
                        const domain::Employee& employee) const override;

    std::optional<domain::Timesheet> getTimesheet(const domain::UserId& user_id,
                                                  const domain::AdminCategoryId& admin_category_id,
                                                  const domain::DepartmentId& department_id,
                                                  std::chrono::year_month year_month) const override;

private:
    const UowFactoryInterface& uow_factory_;
    const PermissionServiceFactoryInterface& permission_service_factory_;
    const UserServiceFactoryInterface& user_service_factory_;
    const TimesheetServiceFactoryInterface& timesheet_service_factory_;
    const ShopServiceFactoryInterface& shop_service_factory_;
};

}  // namespace application
