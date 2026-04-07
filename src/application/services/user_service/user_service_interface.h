#pragma once

#include "domain/interfaces/repositorys/users_repository_interface.h"
#include "domain/entities/user/user.h"

#include <optional>

namespace application {

class UserServiceInterface{
public:
    virtual ~UserServiceInterface() = default;

    virtual std::optional<domain::User> Login (const domain::UserLoginData& user_login_data) const = 0;
};

} // namespace application