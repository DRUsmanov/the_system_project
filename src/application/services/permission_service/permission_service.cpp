#include "permission_service.h"

#include "domain/entities/permission/permission.h"
using namespace application;

bool PermissionService::checkUserAddEmployeePermission(const domain::UserId& user_id,
                                                       const domain::DepartmentId& department_id) const {
    std::optional<domain::UserPermissions> user_permissions = permission_repository_->downloadUserPermissions(user_id);

    if (!user_permissions.has_value()) {
        return false;
    }

    auto it = user_permissions->find(department_id);

    if (it == user_permissions->end()) {
        return false;
    }

    return it->second.hasPermission(domain::PermissionsType::WRITE);
}