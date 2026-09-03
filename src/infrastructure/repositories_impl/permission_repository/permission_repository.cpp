#include "repositories_impl/permission_repository/permission_repository.h"

#include <cstdint>

#include "connection_pool/querys.h"
#include "entities/permission/permission.h"
#include "entities/shop/department/department.h"
#include "entities/user/user.h"
#include "json_formater/json_formater.h"

using namespace infrastructure;

std::optional<domain::UserPermissions> PermissionRepository::downloadUserPermissions(domain::UserId user_id) const {
    auto result = uow_->execParams(query::DOWNLOAD_USER_PERMISSIONS, *user_id);

    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::UserPermissions user_permissions;

    for (const auto row : result) {
        auto db_deprtment_id = row[tables::permissions::DEPARTMENT_ID].as<uint64_t>();
        domain::DepartmentId department_id{db_deprtment_id};

        auto db_permissions = row[tables::permissions::PERMISSIONS].as<uint64_t>();
        domain::Permissions permissions{static_cast<unsigned long>(db_permissions)};

        user_permissions.emplace(department_id, permissions);
    }

    return user_permissions;
}