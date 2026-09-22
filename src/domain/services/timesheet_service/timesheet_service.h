#pragma once

#include <chrono>
#include <memory>
#include <optional>

#include "repositories/timesheet_repository_interface.h"
#include "services/timesheet_service/timesheet_service_interface.h"

namespace domain {

using namespace std::chrono;
using namespace std::literals;

class TimesheetService : public TimesheetServiceInterface {
public:
    TimesheetService(std::shared_ptr<TimeSheetRepositoryInterface> timesheet_repository) :
        timesheet_repository_{timesheet_repository} {}

    std::optional<Timesheet> getDepartmentTimesheet(DepartmentId department_id,
                                                    AdminCategoryId admin_category_id,
                                                    std::chrono::year_month year_month) const override;
    bool generateTimesheetForAllEmployees(const EmployeeAssignments& employee_assignments,
                                          std::chrono::year year) override;
    bool generateTimesheetForNewEmployee(const EmployeeId& employee_id,
                                         const Employee& employee,
                                         const EmployeeAssignment& employee_assignment) override;
    bool updateTimesheetForEmployee(const EmployeeId& employee_id,
                                    const EmployeeAssignment& employee_assignment,
                                    const domain::Date& assignment_changing_date) override;
    bool removeTimesheetForEmployeeFromDate(const EmployeeId& employee_id, const domain::Date& removin_date) override;
    std::optional<WorkSchedules> getWorkSchedules() const override;
    std::optional<Date> getMaxDateInTimesheet() const override;
    const LeaveTypeDescriptions& getLeaveTypeDescriptions() const override;

private:
    struct TimesheetGenerationContext {
        const AdminCategoryId& admin_category_id;
        const Date& date;
        const EmployeeId& employee_id;
        const DepartmentId& department_id;
        const StaffPositionId& staff_position_id;
        const WorkScheduleId& work_schedule_id;
        const WorkSchedule& work_schedule;
        std::optional<const PreHolidays> pre_holidays;
        std::optional<const Holidays> holidays;
        std::optional<const ExtraHolidays> extra_holidays;
        std::optional<const EmployeeVacations> employee_vacations;
    };

private:
    bool generateEmployeeVacationsInTimesheet(Timesheet& timesheet,
                                              const TimesheetGenerationContext& generation_context);
    bool generateHolidaysAndPreHolidaysInTimesheet(Timesheet& timesheet,
                                                   const TimesheetGenerationContext& generation_context);
    bool generateWorkingAndNonWorkingDayInTimesheet(Timesheet& timesheet,
                                                    const TimesheetGenerationContext& generation_context);
    std::chrono::year_month_day getCurrentDate() const;

private:
    std::shared_ptr<TimeSheetRepositoryInterface> timesheet_repository_;
    const std::chrono::sys_days system_start_date = 2026y / September / 1;
};

}  // namespace domain
