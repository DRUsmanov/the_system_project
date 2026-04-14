#pragma once

#include "domain/interfaces/repositorys/users_repository_interface.h"
#include "infrastructure/uow_impl/uow_impl.h"

#include <memory>

namespace infrastructure {

class UserRepository : public domain::UsersRepositoryInterface {
public:
    UserRepository(std::shared_ptr<Uow> uow)
    : uow_{uow} { }

    std::optional<domain::User> DownloadUser(const domain::UserLoginData& login_data) const override;

private:
    std::shared_ptr<Uow> uow_;
};

} // namespace infrastructure
