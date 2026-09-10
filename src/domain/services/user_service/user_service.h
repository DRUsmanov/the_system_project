#pragma once

#include <memory>

#include "repositories/users_repository_interface.h"
#include "services/user_service/user_service_interface.h"

namespace domain {

class UserService : public UserServiceInterface {
public:
    explicit UserService(std::shared_ptr<UsersRepositoryInterface> user_repository) :
        user_repository_{user_repository} {}

    std::optional<User> login(std::string login, std::string password) const override;
    std::optional<User> getUser(const UserId& user_id) const override;

private:
    std::shared_ptr<UsersRepositoryInterface> user_repository_;
};

}  // namespace domain
