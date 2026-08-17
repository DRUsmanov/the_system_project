#pragma once

#include <chrono>

#include "application/dto_mappers/shop_dto_mapper/shop_dto_mapper_interface.h"
#include "application/dto_mappers/user_dto_mapper/user_dto_mapper_interface.h"
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
                       const ShopServiceFactoryInterface& shop_service_factory,
                       const UserDtoMapperInterface& user_dto_mapper,
                       const ShopDtoMapperInterface& shop_dto_mapper) :
        uow_factory_{uow_factory}, permission_service_factory_{permission_service_factory},
        user_service_factory_{user_service_factory}, timesheet_service_factory_{timesheet_service_factory},
        shop_service_factory_{shop_service_factory}, user_dto_mapper_{user_dto_mapper},
        shop_dto_mapper_{shop_dto_mapper} {}

    std::optional<UserIdOutputDto> login(const UserLoginInputDto& user_login_input_dto) const override;

    bool addEmployee(const UserIdInputDto& user_id_input_dto,
                     const AddEmployeeInputDto& add_employee_input_dto) const override;

    std::optional<TimesheetOutputDto> getTimesheet(const TimesheetInputDto& timesheet_input_dto) const override;

private:
    const UowFactoryInterface& uow_factory_;
    const PermissionServiceFactoryInterface& permission_service_factory_;
    const UserServiceFactoryInterface& user_service_factory_;
    const TimesheetServiceFactoryInterface& timesheet_service_factory_;
    const ShopServiceFactoryInterface& shop_service_factory_;

    const UserDtoMapperInterface& user_dto_mapper_;
    const ShopDtoMapperInterface& shop_dto_mapper_;
};

}  // namespace application
