#pragma once

#include "user_dto_mapper_interface.h"

namespace application {

class UserDtoMapper : public  UserDtoMapperInterface{
public:
    domain::UserLoginData Convert(const UserLoginInputDto& user_login_input_dto) const override;
    UserIdOutputDto Convert(const domain::User& user) const override;

    domain::UserId Convert(const UserIdInputDto& user_id_input_dto) const override;
};
    
} // namespace application
