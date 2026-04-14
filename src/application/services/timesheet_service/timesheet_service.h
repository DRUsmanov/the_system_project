#pragma once

#include "timesheet_service_interface.h"

#include <chrono>
#include <optional>
#include <memory>

namespace application{

class TimesheetService : public TimesheetServiceInterface{
public:
    TimesheetService(std::shared_ptr<domain::TimeSheetRepositoryInterface> timesheet_repository)
    : timesheet_repository_{timesheet_repository} { }

    std::optional<domain::Timesheet> GetTimesheet(domain::DepartmentId department_id, domain::AdminCategoryId admin_category_id
                                    , std::chrono::year_month year_month) const override;
    domain::Timesheet GenerateTimesheet(const domain::Shop& shop, std::chrono::year year) override;
    bool AddTimesheet(const domain::Timesheet& timesheet) override;

private:
    struct TimesheetGenerationContext {
        const domain::AdminCategoryId& admin_category_id;
        const domain::Date& date;
        const domain::EmployeeId& employee_id;
        const domain::DepartmentId& department_id;
        const domain::StaffPositionId& staff_position_id;
        const domain::WorkScheduleId& work_schedule_id;
        const domain::WorkSchedule& work_schedule;
        const domain::PreHolidays& pre_holidays;
        const domain::Holidays& holidays;
        const domain::ExtraHolidays& extra_holidays;
        const domain::Vacations& vacations;
    };

    bool GenerateEmployeeVacationsInTimesheet(domain::Timesheet& timesheet, const TimesheetGenerationContext& generation_context);
    bool GenerateHolidaysInTimesheet(domain::Timesheet& timesheet, const TimesheetGenerationContext& generation_context);
    bool GenerateWorkingDayInTimesheet(domain::Timesheet& timesheet, const TimesheetGenerationContext& generation_context);

    std::shared_ptr<domain::TimeSheetRepositoryInterface> timesheet_repository_;
};

} // namespace application

