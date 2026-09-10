#pragma once

#include "entities/shop/department/department.h"
#include "entities/user/user.h"

namespace domain {

class PermissionServiceInterface {
public:
    virtual ~PermissionServiceInterface() = default;

    virtual bool checkUserDepartmentWritePermission(const UserId& user_id, const DepartmentId& department_id) const = 0;
    virtual bool checkUserDepartmentReadPermission(const UserId& user_id, const DepartmentId& department_id) const = 0;
};

}  // namespace domain
