#pragma once

#include "application/dto/user_dto.h"
#include "application/dto/timesheet_dto.h"

#include <chrono>
#include <optional>

namespace application{

class ApplicationManagerInterface{
public:
    virtual ~ApplicationManagerInterface() = default;

    virtual std::optional<UserIdOutputDto> Login(const UserLoginInputDto& user_login_input_dto) const = 0;

    virtual std::optional<TimesheetOutputDto> GetTimesheet(const TimesheetInputDto& timesheet_input_dto) const = 0;
    virtual std::optional<UserIdOutputDto> GetUser(const UserLoginInputDto user_login_input_dto) const = 0;    
};
    
} // namespace application
