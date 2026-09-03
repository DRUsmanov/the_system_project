#include "application_gateway/application_gateway.h"

using namespace application;

std::optional<UserLoginResponseDto> ApplicationGateway::login(const UserLoginRequestDto& user_login_request_dto) const {
    auto user_login_data = user_dto_mapper_.convert(user_login_request_dto);
    auto user = application_manager_.login(user_login_data.login, user_login_data.password);

    if (user.has_value()) {
        return user_dto_mapper_.convert(user.value());
    }

    return std::nullopt;
}

bool application::ApplicationGateway::addEmployee(const UserAccessDto& user_access_dto,
                                                  const AddEmployeeRequestDto& add_employee_request_dto) const {
    auto user_id = user_dto_mapper_.convert(user_access_dto);
    auto [employee_assignment, employee] = shop_dto_mapper_.convert(add_employee_request_dto);
    return application_manager_.addEmployee(user_id, employee_assignment, employee);
}

std::optional<GetTimesheetResponseDto> application::ApplicationGateway::getTimesheet(
    const UserAccessDto& user_access_dto,
    const GetTimesheetRequestDto& get_timesheet_input_dto) const {
    return std::optional<GetTimesheetResponseDto>();
}
