#pragma once

#include <optional>

#include "domain/entities/user/user.h"
#include "domain/interfaces/repositorys/users_repository_interface.h"

namespace application {

class UserServiceInterface {
public:
    virtual ~UserServiceInterface() = default;

    virtual std::optional<domain::User> login(const domain::UserLoginData& user_login_data) const = 0;
    virtual std::optional<domain::User> getUser(const domain::UserId& user_id) const = 0;
};

}  // namespace application