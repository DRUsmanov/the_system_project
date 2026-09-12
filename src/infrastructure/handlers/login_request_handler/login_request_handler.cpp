#include "login_request_handler.h"

using namespace infrastructure;

namespace response_keys {
constexpr std::string_view LAST_NAME{"last_name"};
constexpr std::string_view FIRST_NAME{"first_name"};
constexpr std::string_view PATRONYMIC{"patronymic"};
constexpr std::string_view AUTH_TOKEN{"auth_token"};
}  // namespace response_keys

std::string LoginRequestHandler::makeAcceptedAnswer(
    const TokenManager::Token& token,
    const application::UserLoginResponseDto& user_login_response_dto) const {
    json::object response;
    response[response_keys::AUTH_TOKEN] = *token;
    response[response_keys::LAST_NAME] = user_login_response_dto.last_name;
    response[response_keys::FIRST_NAME] = user_login_response_dto.first_name;
    response[response_keys::PATRONYMIC] = user_login_response_dto.patronymic;
    return serializeObject(response);
}