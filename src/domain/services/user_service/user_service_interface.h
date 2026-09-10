#pragma once

#include <optional>
#include <string>

#include "entities/user/user.h"
#include "repositories/users_repository_interface.h"

namespace domain {

class UserServiceInterface {
public:
    virtual ~UserServiceInterface() = default;

    virtual std::optional<User> login(std::string login, std::string password) const = 0;
    virtual std::optional<User> getUser(const UserId& user_id) const = 0;
};

}  // namespace domain