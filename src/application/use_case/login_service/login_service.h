#pragma once

#include "../../../domain/interfaces/repositorys/users_repository.h"
#include "../../dto/login_dto.h"

#include <unordered_map>

namespace application {

class LoginService{
public:
   explicit LoginService(domain::UsersRepositoryInterface& user_repository_interface)
    : user_repository_interface_{user_repository_interface}{ }

    const OutputLoginDto Login (const InputLoginDto& input_login_dto) const;

private:
    const domain::UsersRepositoryInterface& user_repository_interface_;
};

}

