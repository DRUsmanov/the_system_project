#pragma once

#include "application/dto/user_dto.h"
#include "domain/entities/user/user.h"

namespace application {

class UserDtoMapperInterface {
public:
    virtual ~UserDtoMapperInterface() = default;

    virtual domain::UserLoginData Convert(const UserLoginInputDto& user_login_input_dto) const = 0;
    virtual UserIdOutputDto Convert(const domain::User& user) const = 0;
};
    
} // namespace application
