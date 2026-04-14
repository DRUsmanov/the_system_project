#pragma once

#include "utils/tagged.h"

#include <string>

namespace domain {

namespace detail {
    struct UserIdTag{};
} // namespace detail

using UserId = utils::Tagged<int, detail::UserIdTag>;
using UserIdHasher = utils::TaggedHasher<UserId>;

struct User {
    int user_id;
    int employee_id;
    int64_t permissions;
    int admin_category_id;
};

struct UserLoginData{
    std::string login;
    std::string password;
};

} // namespace domain

