#pragma once

#include <memory>

#include "repositories/users_repository_interface.h"
#include "uow_impl/uow_impl.h"

namespace infrastructure {

class UserRepository : public domain::UsersRepositoryInterface {
public:
    UserRepository(std::shared_ptr<Uow> uow) : uow_{uow} {}

    std::optional<domain::User> loginUser(std::string login, std::string password) const override;
    std::optional<domain::User> downloadUser(const domain::UserId& user_id) const override;

private:
    std::shared_ptr<Uow> uow_;
};

}  // namespace infrastructure
