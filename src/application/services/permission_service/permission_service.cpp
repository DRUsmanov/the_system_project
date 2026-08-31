#include "permission_service.h"

#include "domain/entities/permission/permission.h"

using namespace application;

bool PermissionService::checkUserDepartmentWritePermission(const domain::UserId& user_id,
                                                           const domain::DepartmentId& department_id) const {
    auto user_department_permissions = getUserDepartmentPermissions(user_id, department_id);

    if (user_department_permissions.has_value()) {
        return user_department_permissions->hasPermission(domain::PermissionsType::WRITE);
    }

    return false;
}

bool application::PermissionService::checkUserDepartmentReadPermission(
    const domain::UserId& user_id,
    const domain::DepartmentId& department_id) const {
    auto user_department_permissions = getUserDepartmentPermissions(user_id, department_id);

    if (user_department_permissions.has_value()) {
        return user_department_permissions->hasPermission(domain::PermissionsType::READ);
    }

    return false;
}

std::optional<domain::Permissions> application::PermissionService::getUserDepartmentPermissions(
    const domain::UserId& user_id,
    const domain::DepartmentId& department_id) const {
    std::optional<domain::UserPermissions> user_permissions = permission_repository_->downloadUserPermissions(user_id);

    if (user_permissions.has_value()) {
        auto it = user_permissions->find(department_id);

        if (it == user_permissions->end()) {
            return std::nullopt;
        }

        return it->second;
    }
}
