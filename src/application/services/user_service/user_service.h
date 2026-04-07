#pragma once

#include "domain/interfaces/repositorys/users_repository_interface.h"
#include "application/services/user_service/user_service_interface.h"

#include <unordered_map>

namespace application {

class UserService : public UserServiceInterface{
public:
   explicit UserService(domain::UsersRepositoryInterface& user_repository_interface)
    : user_repository_interface_{user_repository_interface}{ }

    std::optional<domain::User> Login (const domain::UserLoginData& user_login_data) const override;

private:
    const domain::UsersRepositoryInterface& user_repository_interface_;
};

}

