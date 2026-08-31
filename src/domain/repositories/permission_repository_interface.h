#pragma once

#include <optional>

#include "domain/entities/permission/permission.h"
#include "domain/entities/shop/department/department.h"
#include "domain/entities/shop/shop.h"

namespace domain {

class PermissionRepositoryInterface {
public:
    virtual ~PermissionRepositoryInterface() = default;

    virtual std::optional<UserPermissions> downloadUserPermissions(domain::UserId user_id) const = 0;
};

}  // namespace domain
