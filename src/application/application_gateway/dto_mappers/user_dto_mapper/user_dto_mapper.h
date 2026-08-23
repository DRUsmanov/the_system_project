#pragma once

#include "user_dto_mapper_interface.h"

namespace application {

class UserDtoMapper : public UserDtoMapperInterface {
public:
    domain::UserLoginData convert(const UserLoginRequestDto& user_login_request_dto) const override;
    UserLoginResponseDto convert(const domain::User& user) const override;

    domain::UserId convert(const UserAccessDto& user_access_dto) const override;
};

}  // namespace application
