// Управляет пользователями системы
#pragma once

#include "domain/entities/user/user.h"


#include <optional>

namespace domain{

class UsersRepositoryInterface{
public:
    virtual std::optional<User> DownloadUser(const UserLoginData& login_data) const = 0;
};

} // namspace domain

