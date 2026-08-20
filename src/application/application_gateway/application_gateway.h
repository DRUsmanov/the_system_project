#pragma once

#include "application/application_gateway/application_gateway_interface.h"
#include "application/application_gateway/dto_mappers/shop_dto_mapper/shop_dto_mapper_interface.h"
#include "application/application_gateway/dto_mappers/timesheet_dto_mapper/timesheet_dto_mapper_interface.h"
#include "application/application_gateway/dto_mappers/user_dto_mapper/user_dto_mapper_interface.h"
#include "application/application_manager_interface.h"

namespace application {

class ApplicationGateway : public ApplicationGatewayInterface {
public:
    ApplicationGateway(ApplicationManagerInterface& application_manager,
                       const ShopDtoMapperInterface& shop_dto_mapper,
                       const UserDtoMapperInterface& user_dto_mapper) :
        application_manager_{application_manager}, shop_dto_mapper_{shop_dto_mapper},
        user_dto_mapper_{user_dto_mapper} {}

    std::optional<UserIdOutputDto> login(const UserLoginInputDto& user_login_input_dto) const override;

    bool addNewEmployee(const UserIdInputDto& user_id_input_dto,
                        const AddEmployeeInputDto& add_eployee_input_dto) const override;

    std::optional<TimesheetOutputDto> getTimesheet(const UserIdInputDto& user_id_input_dto,
                                                   const GetTimesheetInputDto& get_timesheet_input_dto) const override;

    std::optional<UserIdOutputDto> getUser(const UserIdInputDto& user_id_input_dto) const override;

private:
    ApplicationManagerInterface& application_manager_;
    const ShopDtoMapperInterface& shop_dto_mapper_;
    const UserDtoMapperInterface& user_dto_mapper_;
};

}  // namespace application