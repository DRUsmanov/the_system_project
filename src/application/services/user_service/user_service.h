#pragma once

#include "domain/interfaces/repositorys/users_repository_interface.h"
#include "application/services/user_service/user_service_interface.h"

#include <memory>

namespace application {

class UserService : public UserServiceInterface{
public:
   explicit UserService(std::shared_ptr<domain::UsersRepositoryInterface> user_repository)
    : user_repository_{user_repository}{ }

    std::optional<domain::User> Login (const domain::UserLoginData& user_login_data) const override;

private:
    std::shared_ptr<domain::UsersRepositoryInterface> user_repository_;
};

}

