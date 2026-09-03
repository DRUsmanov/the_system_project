#include "application_gateway/dto_mappers/user_dto_mapper/user_dto_mapper.h"

using namespace application;

domain::UserLoginData UserDtoMapper::convert(const UserLoginRequestDto& user_login_request_dto) const {
    domain::UserLoginData user_login_data;
    user_login_data.login = user_login_request_dto.login;
    user_login_data.password = user_login_request_dto.password;
    return user_login_data;
}

UserLoginResponseDto application::UserDtoMapper::convert(const domain::User& user) const {
    UserLoginResponseDto user_login_response_dto;
    user_login_response_dto.user_id = *user.user_id;
    user_login_response_dto.employee_id = *user.employee_id;
    return user_login_response_dto;
}

domain::UserId UserDtoMapper::convert(const UserAccessDto& user_access_dto) const {
    return domain::UserId{user_access_dto.user_id};
}
