#pragma once

#include <string>

namespace domain {

struct UserLoginData{
    std::string login;
    std::string password;
};

struct User {
    int user_id;
    int permissions;
    int admin_category_id;
};

} // namespace domain

