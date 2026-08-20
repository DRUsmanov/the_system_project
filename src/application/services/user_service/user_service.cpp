#include "user_service.h"

namespace application {

std::optional<domain::User> UserService::login(std::string login, std::string password) const {
    return user_repository_->loginUser(login, password);
}

std::optional<domain::User> UserService::getUser(const domain::UserId& user_id) const {
    return user_repository_->downloadUser(user_id);
}

}  // namespace application