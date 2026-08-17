#include "user_service.h"

namespace application {

std::optional<domain::User> UserService::login(const domain::UserLoginData& user_login_data) const {
    return user_repository_->loginUser(user_login_data);
}

std::optional<domain::User> UserService::getUser(const domain::UserId& user_id) const {
    return user_repository_->downloadUser(user_id);
}

}  // namespace application