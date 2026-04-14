#pragma once

#include "application_manager_interface.h"
#include "application/factorys/uow_factory_interface.h"
#include "application/factorys/user_service_factory_interface.h"
#include "application/factorys/timesheet_service_factory_interface.h"
#include "application/factorys/shop_service_factory_interface.h"
#include "application/dto_mappers/user_dto_mapper/user_dto_mapper_interface.h"


#include <chrono>

namespace application{

class ApplicationManager : public ApplicationManagerInterface {
public:
    ApplicationManager(
        const UowFactoryInterface& uow_factory,
        const UserServiceFactoryInterface& user_service_factory,
        const TimesheetServiceFactoryInterface& timesheet_service_factory,
        const ShopServiceFactoryInterface& shop_service_factory,
        const UserDtoMapperInterface& user_dto_mapper
    )
    : uow_factory_{uow_factory}
    , user_service_factory_{user_service_factory}
    , timesheet_service_factory_{timesheet_service_factory} 
    , shop_service_factory_{shop_service_factory}
    , user_dto_mapper_{user_dto_mapper}{ }

    std::optional<UserIdOutputDto> Login(const UserLoginInputDto& user_login_input_dto) const override;

    std::optional<TimesheetOutputDto> GetTimesheet(const TimesheetInputDto& timesheet_input_dto) const override;

private:
    const UowFactoryInterface& uow_factory_;
    const UserServiceFactoryInterface& user_service_factory_;
    const TimesheetServiceFactoryInterface& timesheet_service_factory_;
    const ShopServiceFactoryInterface& shop_service_factory_;

    const UserDtoMapperInterface& user_dto_mapper_;
};
    
} // namespace application
