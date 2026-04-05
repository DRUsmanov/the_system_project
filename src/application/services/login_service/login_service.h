#pragma once

#include "domain/interfaces/repositorys/users_repository_interface.h"
#include "application/services/login_service/login_service_interface.h"

#include <unordered_map>

namespace application {

class LoginService : public LoginServiceInterface{
public:
   explicit LoginService(domain::UsersRepositoryInterface& user_repository_interface)
    : LoginServiceInterface{user_repository_interface}{ }

    domain::User Login (const domain::LoginData& login_data) const override;
};

}

