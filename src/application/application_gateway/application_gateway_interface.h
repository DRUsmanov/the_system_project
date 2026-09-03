#pragma once

#include "application_gateway/dto/shop_dto.h"
#include "application_gateway/dto/timesheet_dto.h"
#include "application_gateway/dto/user_dto.h"

namespace application {

class ApplicationGatewayInterface {
public:
    ~ApplicationGatewayInterface() = default;

    virtual std::optional<UserLoginResponseDto> login(const UserLoginRequestDto& user_login_request_dto) const = 0;

    virtual bool addEmployee(const UserAccessDto& user_access_dto,
                             const AddEmployeeRequestDto& add_employee_request_dto) const = 0;

    virtual std::optional<GetTimesheetResponseDto> getTimesheet(
        const UserAccessDto& user_access_dto,
        const GetTimesheetRequestDto& get_timesheet_input_dto) const = 0;
};

}  // namespace application
