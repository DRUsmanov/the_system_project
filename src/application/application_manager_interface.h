#pragma once

#include <chrono>
#include <optional>

#include "application/dto/shop_dto.h"
#include "application/dto/timesheet_dto.h"
#include "application/dto/user_dto.h"

namespace application {

class ApplicationManagerInterface {
public:
    virtual ~ApplicationManagerInterface() = default;

    virtual std::optional<UserIdOutputDto> login(const UserLoginInputDto& user_login_input_dto) const = 0;

    virtual bool addEmployee(const UserIdInputDto& user_id_input_dto,
                             const AddEmployeeInputDto& add_employee_input_dto) const = 0;
    virtual std::optional<TimesheetOutputDto> getTimesheet(const TimesheetInputDto& timesheet_input_dto) const = 0;
    virtual std::optional<UserIdOutputDto> getUser(const UserLoginInputDto user_login_input_dto) const = 0;
};

}  // namespace application
