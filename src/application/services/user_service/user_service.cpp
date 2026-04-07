#include "user_service.h"

namespace application {

std::optional<domain::User> UserService::Login (const domain::UserLoginData& user_login_data) const {
    return user_repository_interface_.DownloadUser(user_login_data);
}

} // namespace application