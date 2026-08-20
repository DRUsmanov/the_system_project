#pragma once

#include <memory>

#include "application/services/user_service/user_service_interface.h"
#include "domain/interfaces/repositorys/users_repository_interface.h"

namespace application {

class UserService : public UserServiceInterface {
public:
    explicit UserService(std::shared_ptr<domain::UsersRepositoryInterface> user_repository) :
        user_repository_{user_repository} {}

    std::optional<domain::User> login(std::string login, std::string password) const override;
    std::optional<domain::User> getUser(const domain::UserId& user_id) const override;

private:
    std::shared_ptr<domain::UsersRepositoryInterface> user_repository_;
};

}  // namespace application
