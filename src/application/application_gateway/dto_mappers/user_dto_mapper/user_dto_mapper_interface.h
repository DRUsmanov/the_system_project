#pragma once

#include "application/application_gateway/dto/user_dto.h"
#include "domain/entities/user/user.h"

namespace application {

class UserDtoMapperInterface {
public:
    virtual ~UserDtoMapperInterface() = default;

    virtual domain::UserLoginData convert(const UserLoginInputDto& user_login_input_dto) const = 0;
    virtual UserIdOutputDto convert(const domain::User& user) const = 0;

    virtual domain::UserId convert(const UserIdInputDto& user_id_input_dto) const = 0;
};

}  // namespace application
