// Управляет пользователями системы
#pragma once

#include "domain/entities/user/user.h"


#include <optional>

namespace domain{

class UsersRepositoryInterface{
public:
    virtual std::optional<const User&> Login(const LoginData& login_data) const = 0;
};

} // namspace domain

