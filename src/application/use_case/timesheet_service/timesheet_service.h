#pragma once

#include "../../../domain/interfaces/repositorys/timesheet_repository.h"

namespace application{

class TimeSheetService{
public:
    TimeSheetService(domain::TimeSheetRepositoryInterface& timesheet_repository)
    : timesheet_repository_{timesheet_repository} { }

    bool GenerateTimeSheet(int year);
private:
    domain::TimeSheetRepositoryInterface& timesheet_repository_;
};

} // namespace application

