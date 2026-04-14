#pragma once

#include <string>

namespace application {

struct UserLoginInputDto{
    std::string login;
    std::string password;
};

struct UserIdInputDto{
    int user_id;
};

struct UserIdOutputDto{
    int user_id;
    int employee_id;
};


} // namespace application

