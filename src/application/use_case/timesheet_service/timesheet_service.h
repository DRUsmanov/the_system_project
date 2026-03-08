#pragma once

#include "domain/interfaces/repositorys/timesheet_repository.h"

#include <chrono>

namespace application{

class TimeSheetService{
public:
    TimeSheetService(domain::TimeSheetRepositoryInterface& timesheet_repository)
    : timesheet_repository_{timesheet_repository} { }

    bool GenerateTimeSheet(std::chrono::year year);
private:
    domain::TimeSheetRepositoryInterface& timesheet_repository_;
    
};

} // namespace application

