// Управляет пользователями системы
#pragma once

#include <optional>

#include "domain/entities/user/user.h"

namespace domain {

class UsersRepositoryInterface {
public:
    virtual std::optional<User> loginUser(const UserLoginData& user_login_data) const = 0;
    virtual std::optional<User> downloadUser(const UserId& user_id) const = 0;
};

}  // namespace domain