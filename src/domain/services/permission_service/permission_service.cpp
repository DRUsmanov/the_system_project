#include "services/permission_service/permission_service.h"

#include "entities/permission/permission.h"
#include "logger.h"

using namespace domain;

bool PermissionService::checkUserDepartmentWritePermission(const UserId& user_id,
                                                           const DepartmentId& department_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_department_permissions = getUserDepartmentPermissions(user_id, department_id);

    if (user_department_permissions.has_value()) {
        return user_department_permissions->hasPermission(PermissionsType::WRITE);
    }

    return false;
}

bool PermissionService::checkUserDepartmentReadPermission(const UserId& user_id,
                                                          const DepartmentId& department_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto user_department_permissions = getUserDepartmentPermissions(user_id, department_id);

    if (user_department_permissions.has_value()) {
        return user_department_permissions->hasPermission(PermissionsType::READ);
    }

    return false;
}

std::optional<Permissions> PermissionService::getUserDepartmentPermissions(const UserId& user_id,
                                                                           const DepartmentId& department_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    std::optional<UserPermissions> user_permissions = permission_repository_->downloadUserPermissions(user_id);

    if (user_permissions.has_value()) {
        auto it = user_permissions->find(department_id);

        if (it == user_permissions->end()) {
            return std::nullopt;
        }

        return it->second;
    }

    return std::nullopt;
}
