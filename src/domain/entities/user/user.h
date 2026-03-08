#pragma once

#include <string>

namespace domain {

struct LoginData{
    std::string login;
    std::string password;
};

struct User {
    std::string login;
    uint64_t permissions;
};

} // namespace domain

