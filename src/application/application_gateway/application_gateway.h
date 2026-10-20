#pragma once

#include "application_gateway/application_gateway_interface.h"
#include "application_gateway/dto_mappers/shop_dto_mapper/shop_dto_mapper.h"
#include "application_gateway/dto_mappers/timesheet_dto_mapper/timesheet_dto_mapper.h"
#include "application_gateway/dto_mappers/user_dto_mapper/user_dto_mapper.h"
#include "application_manager/application_manager_interface.h"

namespace application {

class ApplicationGateway : public ApplicationGatewayInterface {
public:
    ApplicationGateway(ApplicationManagerInterface& application_manager) : application_manager_{application_manager} {}

    std::optional<UserLoginResponseDto> login(const UserLoginRequestDto& user_login_request_dto) const override;

    std::optional<AddEmployeeResponseDto> addEmployee(
        const UserAccessDto& user_access_dto,
        const AddEmployeeRequestDto& add_employee_request_dto) const override;
    bool removeEmployee(const UserAccessDto& user_access_dto,
                        const RemoveEmployeeRequestDto& remove_employee_request_dto) const override;
    std::optional<GetEmployeeResponseDto> getEmployee(
        const UserAccessDto& user_access_dto,
        const GetEmployeeRequestDto& get_employee_request_dto) const override;
    std::optional<GetDepartmentsResponseDto> getDepartments(const UserAccessDto& user_access_dto) const override;
    std::optional<GetStaffPositionsResponseDto> getStaffPositions(const UserAccessDto& user_access_dto) const override;
    std::optional<GetWorkSchedulesResponseDto> getWorkSchedules(const UserAccessDto& user_access_dto) const override;
    std::optional<GetDepartmentStaffResponseDto> getDepartmentStaff(
        const UserAccessDto& user_access_dto,
        const GetDepartmentStaffRequestDto& get_department_staff_request_dto) const override;
    bool updateEmployee(const UserAccessDto& user_access_dto,
                        const UpdateEmployeeRequestDto& update_employee_request_dto) const override;
    std::optional<GetDepartmentTimesheetResponseDto> getDepartmentTimesheet(
        const UserAccessDto& user_access_dto,
        const GetDepartmentTimesheetRequestDto& get_department_timesheet_request_dto) const override;
    GetLeaveTypesResponseDto getLeaveTypeDescriptions(const UserAccessDto& user_access_dto) const override;
    bool updateEmployeeTimesheetDaysData(const UserAccessDto& user_access_dto,
                                         const UpdateEmployeeTimesheetDaysDataRequestDto&
                                             update_employee_timesheet_days_data_request_dto) const override;
    bool setEmployeeLeaveInTimesheet(const UserAccessDto& user_access_dto,
                                     const SetEmployeeLeaveTypeInTimesheetRequestDto&
                                         set_employee_leave_type_in_timesheet_request_dto) const override;
    bool changeEmployeeAssignmentInTimesheet(const UserAccessDto& user_access_dto,
                                             const ChangeEmployeeAssignmentInTimesheetRequestDto&
                                                 change_employee_assignment_in_timesheet_request_dto) const override;

private:
    ApplicationManagerInterface& application_manager_;
    ShopDtoMapper shop_dto_mapper_;
    UserDtoMapper user_dto_mapper_;
    TimesheetDtoMapper timesheet_dto_mapper_;
};

}  // namespace application