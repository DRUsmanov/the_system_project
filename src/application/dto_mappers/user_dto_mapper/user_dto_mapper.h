#pragma once

#include "user_dto_mapper_interface.h"

namespace application {

class UserDtoMapper : public UserDtoMapperInterface {
public:
    domain::UserLoginData convert(const UserLoginInputDto& user_login_input_dto) const override;
    UserIdOutputDto convert(const domain::User& user) const override;

    domain::UserId convert(const UserIdInputDto& user_id_input_dto) const override;
};

}  // namespace application
