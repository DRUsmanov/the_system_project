#include "services/user_service/user_service.h"

#include "logger.h"

namespace application {

std::optional<domain::User> UserService::login(std::string login, std::string password) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return user_repository_->loginUser(login, password);
}

std::optional<domain::User> UserService::getUser(const domain::UserId& user_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return user_repository_->downloadUser(user_id);
}

}  // namespace application