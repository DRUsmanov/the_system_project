#pragma once

#include "user_dto_mapper_interface.h"
#include "application/dto/user_dto.h"
#include "domain/entities/user/user.h"

namespace application {

class UserDtoMapper : public  UserDtoMapperInterface{
public:
    domain::UserLoginData Convert(const UserLoginInputDto& user_login_input_dto) const override;
    UserIdOutputDto Convert(const domain::User& user) const override;
};
    
} // namespace application
