#pragma once

#include "application/application_gateway/application_gateway_interface.h"
#include "application/application_gateway/dto_mappers/shop_dto_mapper/shop_dto_mapper.h"
#include "application/application_gateway/dto_mappers/timesheet_dto_mapper/timesheet_dto_mapper_interface.h"
#include "application/application_gateway/dto_mappers/user_dto_mapper/user_dto_mapper.h"
#include "application/application_manager/application_manager_interface.h"

namespace application {

class ApplicationGateway : public ApplicationGatewayInterface {
public:
    ApplicationGateway(ApplicationManagerInterface& application_manager) : application_manager_{application_manager} {}

    std::optional<UserLoginResponseDto> login(const UserLoginRequestDto& user_login_request_dto) const override;

    bool addEmployee(const UserAccessDto& user_access_dto,
                     const AddEmployeeRequestDto& add_employee_request_dto) const override;

    std::optional<GetTimesheetResponseDto> getTimesheet(
        const UserAccessDto& user_access_dto,
        const GetTimesheetRequestDto& get_timesheet_input_dto) const override;

private:
    ApplicationManagerInterface& application_manager_;
    ShopDtoMapper shop_dto_mapper_;
    UserDtoMapper user_dto_mapper_;
};

}  // namespace application