#include "login_service.h"

namespace application {

domain::User LoginService::Login (const domain::LoginData& login_data) const {
    auto user = user_repository_interface_.DownloadUser(login_data);

    if (user.has_value()){
        return OutputLoginDto{true, user->login, user->permissions};
    }
    else {
        return OutputLoginDto{};
    }
}

} // namespace application