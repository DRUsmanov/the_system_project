#pragma once

#include "application/dto/user_dto.h"
#include "application/dto/timesheet_dto.h"

#include <chrono>
#include <optional>

namespace application{

class ApplicationManagerInterface{
public:
    virtual ~ApplicationManagerInterface() = default;

    virtual std::optional<OutputTimesheetDto> GetTimesheet(const InputTimesheetDto& input_timesheet_dto) const = 0;
    virtual std::optional<OutputUserDto> GetUser(const InputUserDto& input_user_dto) const = 0;    
};
    
} // namespace application
