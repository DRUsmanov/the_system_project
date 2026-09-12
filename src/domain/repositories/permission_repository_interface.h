#pragma once

#include <optional>

#include "entities/permission/permission.h"
#include "entities/shop/department/department.h"
#include "entities/shop/employee_assignments.h"
#include "entities/user/user.h"

namespace domain {

class PermissionRepositoryInterface {
public:
    virtual ~PermissionRepositoryInterface() = default;

    virtual std::optional<UserPermissions> downloadUserPermissions(UserId user_id) const = 0;
};

}  // namespace domain
