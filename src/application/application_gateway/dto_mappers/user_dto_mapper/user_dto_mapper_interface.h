#pragma once

#include "application_gateway/dto/user_dto.h"
#include "entities/user/user.h"

namespace application {

class UserDtoMapperInterface {
public:
    virtual ~UserDtoMapperInterface() = default;

    virtual domain::UserLoginData convert(const UserLoginRequestDto& user_login_request_dto) const = 0;
    virtual UserLoginResponseDto convert(const domain::User& user) const = 0;

    virtual domain::UserId convert(const UserAccessDto& user_access_dto) const = 0;
};

}  // namespace application
