#include "permission_repository.h"

#include "domain/entities/permission/permission.h"
#include "domain/entities/shop/department/department.h"
#include "domain/entities/user/user.h"
#include "infrastructure/connection_pool/querys.h"
#include "infrastructure/json_formater/json_formater.h"

using namespace infrastructure;

std::optional<domain::UserPermissions> PermissionRepository::downloadUserPermissions(domain::UserId user_id) const {
    auto result = uow_->execParams(query::DOWNLOAD_USER_PERMISSIONS, *user_id);

    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::UserPermissions user_permissions;

    for (const auto row : result) {
        auto db_deprtment_id = row[tables::permissions::DEPARTMENT_ID].as<int>();
        domain::DepartmentId department_id{db_deprtment_id};

        auto db_permissions = row[tables::permissions::PERMISSIONS].as<int>();
        domain::Permissions permissions{static_cast<unsigned long>(db_permissions)};

        user_permissions.emplace(department_id, permissions);
    }

    return user_permissions;
}