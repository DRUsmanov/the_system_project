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
    bool updateTimesheetForEmployeeFromDate(const EmployeeId& employee_id,
                                            const EmployeeAssignment& employee_assignment,
                                            const domain::Date& assignment_changing_date) override;
    bool removeTimesheetForEmployeeFromDate(const EmployeeId& employee_id, const domain::Date& removin_date) override;
    std::optional<WorkSchedules> getWorkSchedules() const override;
    std::optional<Date> getMaxDateInTimesheet() const override;
    const LeaveTypeDescriptions& getLeaveTypeDescriptions() const override;
    bool updateEmployeeTimesheetDayData(const domain::EmployeeId& employee_id,
                                        const domain::Date& start_date,
                                        const domain::Date& end_date,
                                        const domain::Timesheet::DayData& updated_day_data,
                                        const AdminCategoryId& admin_category_id,
                                        const EmployeeId& admin_employee_id) override;
    bool setEmployeeLeaveInTimesheet(const domain::EmployeeId& employee_id,
                                     const domain::Date& start_date,
                                     const domain::Date& end_date,
                                     const domain::LeaveType& leave_type,
                                     const AdminCategoryId& admin_category_id,
                                     const EmployeeId& admin_employee_id) override;
    bool changeEmployeeAssignmentInTimesheet(const domain::EmployeeId& employee_id,
                                             const domain::EmployeeAssignment& changed_employee_assignment,
                                             const domain::Date& start_date,
                                             const domain::Date& end_date,
                                             const AdminCategoryId& admin_category_id,
                                             const EmployeeId& admin_employee_id) override;

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
    static bool generateEmployeeVacationsInTimesheet(Timesheet& timesheet,
                                                     const TimesheetGenerationContext& generation_context);
    static bool generateHolidaysAndPreHolidaysInTimesheet(Timesheet& timesheet,
                                                          const TimesheetGenerationContext& generation_context);
    static bool generateWorkingAndNonWorkingDayInTimesheet(Timesheet& timesheet,
                                                           const TimesheetGenerationContext& generation_context);
    bool processEmployeeSickLeaveDuringVacation(domain::Timesheet& employee_timesheet);
    // bool processEmployeeSickLeaveDuringVacationRemoving(Timesheet& employee_timesheet,
    //                                                     const Date start_date,
    //                                                     const Date end_date,
    //                                                     const AdminCategoryId& admin_category_id);
    std::optional<Timesheet> getEmployeeTimesheetBetweenDate(const domain::EmployeeId& employee_id,
                                                             const domain::Date& start_date,
                                                             const domain::Date& end_date,
                                                             const AdminCategoryId& admin_category_id) const;
    std::optional<Timesheet> getEmployeeExtendedVacationsTimesheet(const EmployeeId& employee_id,
                                                                   const AdminCategoryId& admin_category_id,
                                                                   const Date start_date) const;
    static std::chrono::year_month_day getCurrentDate();

private:
    std::shared_ptr<TimeSheetRepositoryInterface> timesheet_repository_;
    const std::chrono::sys_days system_start_date = 2026y / September / 1;
};

}  // namespace domain
