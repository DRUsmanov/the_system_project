#pragma once

#include <chrono>
#include <memory>
#include <optional>

#include "timesheet_service_interface.h"

namespace application {

class TimesheetService : public TimesheetServiceInterface {
public:
    TimesheetService(std::shared_ptr<domain::TimeSheetRepositoryInterface> timesheet_repository) :
        timesheet_repository_{timesheet_repository} {}

    std::optional<domain::Timesheet> getDepartmentTimesheet(domain::DepartmentId department_id,
                                                            domain::AdminCategoryId admin_category_id,
                                                            std::chrono::year_month year_month) const override;
    bool generateTimesheetForShop(const domain::Shop& shop, std::chrono::year year) override;
    bool generateTimesheetForNewEmployee(const domain::Shop::EmployeeAssignment& employee_assignment,
                                         const domain::Employee& employee) override;

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

private:
    bool generateEmployeeVacationsInTimesheet(domain::Timesheet& timesheet,
                                              const TimesheetGenerationContext& generation_context);
    bool generateHolidaysInTimesheet(domain::Timesheet& timesheet,
                                     const TimesheetGenerationContext& generation_context);
    bool generateWorkingDayInTimesheet(domain::Timesheet& timesheet,
                                       const TimesheetGenerationContext& generation_context);
    std::chrono::year_month_day getCurrentData() const;

private:
    std::shared_ptr<domain::TimeSheetRepositoryInterface> timesheet_repository_;
};

}  // namespace application
