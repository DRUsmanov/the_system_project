#include "services/user_service/user_service.h"

#include "logger.h"

using namespace domain;

std::optional<User> UserService::login(std::string login, std::string password) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return user_repository_->loginUser(login, password);
}

std::optional<User> UserService::getUser(const UserId& user_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return user_repository_->downloadUser(user_id);
}
