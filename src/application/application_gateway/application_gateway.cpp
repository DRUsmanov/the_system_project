#include "application_gateway/application_gateway.h"

#include "logger.h"

using namespace application;

std::optional<UserLoginResponseDto> ApplicationGateway::login(const UserLoginRequestDto& user_login_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_login_data = user_dto_mapper_.convert(user_login_request_dto);
    auto user = application_manager_.login(user_login_data.login, user_login_data.password);

    if (user.has_value()) {
        return user_dto_mapper_.convert(user.value());
    }

    return std::nullopt;
}

std::optional<AddEmployeeResponseDto> ApplicationGateway::addEmployee(
    const UserAccessDto& user_access_dto,
    const AddEmployeeRequestDto& add_employee_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto [employee_assignment, employee] = shop_dto_mapper_.convert(add_employee_request_dto);
    auto employee_id = application_manager_.addEmployee(user_id, employee_assignment, employee);

    if (employee_id.has_value()) {
        return shop_dto_mapper_.convert(employee_id.value());
    }

    return std::nullopt;
}

std::optional<RemoveEmployeeResponseDto> ApplicationGateway::removeEmployee(
    const UserAccessDto& user_access_dto,
    const RemoveEmployeeRequestDto& remove_employee_request_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto employee_id = shop_dto_mapper_.convert(remove_employee_request_dto);
    auto is_removed = application_manager_.removeEmployee(user_id, employee_id);

    if (is_removed) {
        return shop_dto_mapper_.convert(is_removed);
    }

    return std::nullopt;
}

std::optional<GetTimesheetResponseDto> application::ApplicationGateway::getTimesheet(
    const UserAccessDto& user_access_dto,
    const GetTimesheetRequestDto& get_timesheet_input_dto) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return std::optional<GetTimesheetResponseDto>();
    // TODO
}
