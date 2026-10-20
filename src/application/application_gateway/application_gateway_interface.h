#pragma once

#include "application_gateway/dto/shop_dto.h"
#include "application_gateway/dto/timesheet_dto.h"
#include "application_gateway/dto/user_dto.h"

namespace application {

class ApplicationGatewayInterface {
public:
    ~ApplicationGatewayInterface() = default;

    virtual std::optional<UserLoginResponseDto> login(const UserLoginRequestDto& user_login_request_dto) const = 0;
    virtual std::optional<AddEmployeeResponseDto> addEmployee(
        const UserAccessDto& user_access_dto,
        const AddEmployeeRequestDto& add_employee_request_dto) const = 0;
    virtual bool removeEmployee(const UserAccessDto& user_access_dto,
                                const RemoveEmployeeRequestDto& remove_employee_request_dto) const = 0;
    virtual std::optional<GetEmployeeResponseDto> getEmployee(
        const UserAccessDto& user_access_dto,
        const GetEmployeeRequestDto& get_employee_request_dto) const = 0;
    virtual std::optional<GetDepartmentsResponseDto> getDepartments(const UserAccessDto& user_access_dto) const = 0;
    virtual std::optional<GetStaffPositionsResponseDto> getStaffPositions(
        const UserAccessDto& user_access_dto) const = 0;
    virtual std::optional<GetWorkSchedulesResponseDto> getWorkSchedules(const UserAccessDto& user_access_dto) const = 0;
    virtual std::optional<GetDepartmentStaffResponseDto> getDepartmentStaff(
        const UserAccessDto& user_access_dto,
        const GetDepartmentStaffRequestDto& get_department_staff_request_dto) const = 0;
    virtual bool updateEmployee(const UserAccessDto& user_access_dto,
                                const UpdateEmployeeRequestDto& update_employee_request_dto) const = 0;
    virtual std::optional<GetDepartmentTimesheetResponseDto> getDepartmentTimesheet(
        const UserAccessDto& user_access_dto,
        const GetDepartmentTimesheetRequestDto& get_department_timesheet_request_dto) const = 0;
    virtual GetLeaveTypesResponseDto getLeaveTypeDescriptions(const UserAccessDto& user_access_dto) const = 0;
    virtual bool updateEmployeeTimesheetDaysData(
        const UserAccessDto& user_access_dto,
        const UpdateEmployeeTimesheetDaysDataRequestDto& update_employee_timesheet_days_data_request_dto) const = 0;
    virtual bool setEmployeeLeaveInTimesheet(
        const UserAccessDto& user_access_dto,
        const SetEmployeeLeaveTypeInTimesheetRequestDto& set_employee_leave_type_in_timesheet_request_dto) const = 0;
    virtual bool changeEmployeeAssignmentInTimesheet(const UserAccessDto& user_access_dto,
                                                     const ChangeEmployeeAssignmentInTimesheetRequestDto&
                                                         change_employee_assignment_in_timesheet_request_dto) const = 0;
};

}  // namespace application
