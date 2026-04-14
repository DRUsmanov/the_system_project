#include "user_dto_mapper.h"

using namespace application;

domain::UserLoginData UserDtoMapper::Convert(const UserLoginInputDto &user_login_input_dto) const {
    domain::UserLoginData user_login_data;
    user_login_data.login = user_login_input_dto.login;
    user_login_data.password = user_login_input_dto.password;
    return user_login_data;
}

UserIdOutputDto application::UserDtoMapper::Convert(const domain::User &user) const {
    UserIdOutputDto user_id_output_dto;
    user_id_output_dto.user_id = user.user_id;
    user_id_output_dto.employee_id = user.employee_id;
    return user_id_output_dto;
}
