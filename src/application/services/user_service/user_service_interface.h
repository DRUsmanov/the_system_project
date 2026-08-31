#pragma once

#include <optional>
#include <string>

#include "domain/entities/user/user.h"
#include "domain/repositories/users_repository_interface.h"

namespace application {

class UserServiceInterface {
public:
    virtual ~UserServiceInterface() = default;

    virtual std::optional<domain::User> login(std::string login, std::string password) const = 0;
    virtual std::optional<domain::User> getUser(const domain::UserId& user_id) const = 0;
};

}  // namespace application