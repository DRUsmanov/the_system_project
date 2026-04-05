#pragma once

#include "domain/interfaces/repositorys/users_repository_interface.h"
#include "domain/entities/user/user.h"

#include <unordered_map>

namespace application {

class LoginServiceInterface{
public:
   explicit LoginServiceInterface(domain::UsersRepositoryInterface& user_repository_interface)
    : user_repository_interface_{user_repository_interface}{ }

    virtual domain::User Login (const domain::LoginData& login_data) const = 0;
protected:
    const domain::UsersRepositoryInterface& user_repository_interface_;
};

} // namespace application