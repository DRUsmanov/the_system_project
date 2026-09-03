// Управляет пользователями системы
#pragma once

#include <optional>
#include <string>

#include "entities/user/user.h"

namespace domain {

class UsersRepositoryInterface {
public:
    virtual std::optional<User> loginUser(std::string login, std::string password) const = 0;
    virtual std::optional<User> downloadUser(const UserId& user_id) const = 0;
};

}  // namespace domain