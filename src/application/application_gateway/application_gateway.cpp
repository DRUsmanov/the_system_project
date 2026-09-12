#include "application_gateway/application_gateway.h"

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
    auto employee_id = application_manager_.addEmployee(user_id, employee_assignment, employee);

    if (!employee_id.has_value()) {
        return std::nullopt;
    }

    return shop_dto_mapper_.convert(employee_id.value());
}

std::optional<RemoveEmployeeResponseDto> ApplicationGateway::removeEmployee(
    const UserAccessDto& user_access_dto,
    const RemoveEmployeeRequestDto& remove_employee_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto employee_id = shop_dto_mapper_.convert(remove_employee_request_dto);
    auto is_removed = application_manager_.removeEmployee(user_id, employee_id);

    if (!is_removed) {
        return std::nullopt;
    }

    return shop_dto_mapper_.convert(is_removed);
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
