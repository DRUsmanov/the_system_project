#pragma once

#include <string>

namespace application {

struct InputUserDto{
    std::string login;
    std::string password;
};

struct OutputUserDto{
    int user_id;
};

} // namespace application

