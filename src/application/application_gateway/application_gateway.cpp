#include "application_gateway.h"

using namespace application;

std::optional<UserIdOutputDto> ApplicationGateway::login(const UserLoginInputDto& user_login_input_dto) const {
    auto user_login_data = user_dto_mapper_.convert(user_login_input_dto);
    auto user = application_manager_.login(user_login_data.login, user_login_data.password);

    if (!user.has_value()) {
        return std::nullopt;
    }

    return user_dto_mapper_.convert(user.value());
}