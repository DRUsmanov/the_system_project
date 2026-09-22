#include "application_gateway/application_gateway.h"

#include <tuple>

#include "entities/timesheet/leave_types/leave_type.h"
#include "logger.h"

using namespace application;

std::optional<UserLoginResponseDto> ApplicationGateway::login(const UserLoginRequestDto& user_login_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_login_data = user_dto_mapper_.convert(user_login_request_dto);
    auto user = application_manager_.login(user_login_data.login, user_login_data.password);

    if (!user.has_value()) {
        return std::nullopt;
    }

    auto employee = application_manager_.getEmployee(user.value().user_id, user.value().employee_id);

    if (!employee.has_value()) {
        return std::nullopt;
    }

    return user_dto_mapper_.convert(user.value(), employee.value());
}

std::optional<AddEmployeeResponseDto> ApplicationGateway::addEmployee(
    const UserAccessDto& user_access_dto,
    const AddEmployeeRequestDto& add_employee_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto [employee_assignment, employee] = shop_dto_mapper_.convert(add_employee_request_dto);
    auto employee_id = application_manager_.addEmployee(user_id, employee, employee_assignment);

    if (!employee_id.has_value()) {
        return std::nullopt;
    }

    return shop_dto_mapper_.convert(employee_id.value());
}

bool ApplicationGateway::removeEmployee(const UserAccessDto& user_access_dto,
                                        const RemoveEmployeeRequestDto& remove_employee_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto [employee_id, removing_date] = shop_dto_mapper_.convert(remove_employee_request_dto);
    return application_manager_.removeEmployee(user_id, employee_id, removing_date);
}

std::optional<GetDepartmentsResponseDto> ApplicationGateway::getDepartments(
    const UserAccessDto& user_access_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto departments = application_manager_.getDepartments(user_id);

    if (!departments) {
        return std::nullopt;
    }

    return shop_dto_mapper_.convert(departments.value());
}

std::optional<GetStaffPositionsResponseDto> ApplicationGateway::getStaffPositions(
    const UserAccessDto& user_access_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto staff_positions = application_manager_.getStaffPositions(user_id);

    if (!staff_positions) {
        return std::nullopt;
    }

    return shop_dto_mapper_.convert(staff_positions.value());
}

std::optional<GetWorkSchedulesResponseDto> ApplicationGateway::getWorkSchedules(
    const UserAccessDto& user_access_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto work_schedules = application_manager_.getWorkSchedules(user_id);

    if (!work_schedules) {
        return std::nullopt;
    }

    return timesheet_dto_mapper_.convert(work_schedules.value());
}

std::optional<GetDepartmentStaffResponseDto> ApplicationGateway::getDepartmentStaff(
    const UserAccessDto& user_access_dto,
    const GetDepartmentStaffRequestDto& get_department_staff_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto department_id = shop_dto_mapper_.convert(get_department_staff_request_dto);

    auto department_staff = application_manager_.getDepartmentStaff(user_id, department_id);

    if (!department_staff.has_value()) {
        return std::nullopt;
    }

    return shop_dto_mapper_.convert(department_staff.value());
}

bool ApplicationGateway::updateEmployee(const UserAccessDto& user_access_dto,
                                        const UpdateEmployeeRequestDto& update_employee_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto update_data = shop_dto_mapper_.convert(update_employee_request_dto);

    const auto& employee_id = std::get<domain::EmployeeId>(update_data);
    const auto& employee = std::get<domain::Employee>(update_data);
    const auto& employee_assignment = std::get<domain::EmployeeAssignment>(update_data);
    const auto& assignment_changing_date = std::get<std::optional<domain::Date>>(update_data);
    return application_manager_.updateEmployee(user_id,
                                               employee_id,
                                               employee,
                                               employee_assignment,
                                               assignment_changing_date);
}

std::optional<GetDepartmentTimesheetResponseDto> ApplicationGateway::getDepartmentTimesheet(
    const UserAccessDto& user_access_dto,
    const GetDepartmentTimesheetRequestDto& get_department_timesheet_request_dto) const {
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto [department_id, date] = timesheet_dto_mapper_.convert(get_department_timesheet_request_dto);

    auto ymd = std::chrono::year_month_day{date};
    auto ym = std::chrono::year_month{ymd.year(), ymd.month()};

    auto department_timesheet = application_manager_.getDepartmentTimesheet(user_id, department_id, ym);

    if (!department_timesheet.has_value()) {
        return std::nullopt;
    }

    auto department_staff = application_manager_.getDepartmentStaff(user_id, department_id);

    if (!department_staff.has_value()) {
        return std::nullopt;
    }

    const auto& employees = department_staff.value().getEmployees();

    auto work_schedules = application_manager_.getWorkSchedules(user_id);

    if (!work_schedules.has_value()) {
        return std::nullopt;
    }

    auto staff_positions = application_manager_.getStaffPositions(user_id);

    if (!staff_positions.has_value()) {
        return std::nullopt;
    }

    return timesheet_dto_mapper_.convert(department_timesheet.value());
}

GetLeaveTypesResponseDto application::ApplicationGateway::getLeaveTypeDescriptions(
    const UserAccessDto& user_access_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto leave_type_desriptions = application_manager_.getLeaveTypeDescriptions(user_id);
    return timesheet_dto_mapper_.convert(leave_type_desriptions);
}
