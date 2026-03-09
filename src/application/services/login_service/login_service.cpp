#include "login_service.h"

namespace application {

const OutputLoginDto LoginService::Login (const InputLoginDto& input_login_dto) const{
    domain::LoginData login_data{input_login_dto.login, input_login_dto.password};
    auto user = user_repository_interface_.Login(login_data);

    if (user.has_value()){
        return OutputLoginDto{true, user->login, user->permissions};
    }
    else {
        return OutputLoginDto{};
    }
}

} // namespace application