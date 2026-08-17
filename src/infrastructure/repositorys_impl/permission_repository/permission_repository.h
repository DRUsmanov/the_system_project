#pragma once

#include <memory>

#include "domain/entities/permission/permission.h"
#include "domain/entities/user/user.h"
#include "domain/interfaces/repositorys/permission_repository_interface.h"
#include "infrastructure/uow_impl/uow_impl.h"

namespace infrastructure {

class PermissionRepository : public domain::PermissionRepositoryInterface {
public:
    PermissionRepository(std::shared_ptr<Uow> uow) : uow_{uow} {}

    std::optional<domain::UserPermissions> downloadUserPermissions(domain::UserId user_id) const override;

private:
    std::shared_ptr<Uow> uow_;
};

}  // namespace infrastructure
