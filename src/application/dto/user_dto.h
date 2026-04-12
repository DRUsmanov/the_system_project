#pragma once

#include <string>

namespace application {

struct UserIdDto{
    int user_id;
};

struct UserLoginDto{
    std::string login;
    std::string password;
};

} // namespace application

