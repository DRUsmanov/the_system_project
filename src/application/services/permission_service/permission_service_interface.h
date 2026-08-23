#pragma once

#include "domain/entities/shop/department/department.h"
#include "domain/entities/user/user.h"

namespace application {

class PermissionServiceInterface {
public:
    virtual ~PermissionServiceInterface() = default;

    virtual bool checkUserDepartmentWritePermission(const domain::UserId& user_id,
                                                    const domain::DepartmentId& department_id) const = 0;
    virtual bool checkUserDepartmentReadPermission(const domain::UserId& user_id,
                                                   const domain::DepartmentId& department_id) const = 0;
};

}  // namespace application
