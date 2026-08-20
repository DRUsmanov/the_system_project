#pragma once

#include "application/application_gateway/dto/shop_dto.h"
#include "application/application_gateway/dto/timesheet_dto.h"
#include "application/application_gateway/dto/user_dto.h"

namespace application {

class ApplicationGatewayInterface {
public:
    ~ApplicationGatewayInterface() = default;

    virtual std::optional<UserIdOutputDto> login(const UserLoginInputDto& user_login_input_dto) const = 0;

    virtual bool addNewEmployee(const UserIdInputDto& user_id_input_dto,
                                const AddEmployeeInputDto& add_eployee_input_dto) const = 0;

    virtual std::optional<TimesheetOutputDto> getTimesheet(
        const UserIdInputDto& user_id_input_dto,
        const GetTimesheetInputDto& get_timesheet_input_dto) const = 0;

    virtual std::optional<UserIdOutputDto> getUser(const UserIdInputDto& user_id_input_dto) const = 0;
};

}  // namespace application
