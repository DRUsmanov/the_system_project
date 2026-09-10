#pragma once

#include <chrono>
#include <memory>

#include "repositories/permission_repository_interface.h"
#include "services/permission_service/permission_service_interface.h"

namespace domain {

class PermissionService : public PermissionServiceInterface {
public:
    PermissionService(std::shared_ptr<PermissionRepositoryInterface> permission_repository) :
        permission_repository_{permission_repository} {}

    bool checkUserDepartmentWritePermission(const UserId& user_id, const DepartmentId& department_id) const override;
    bool checkUserDepartmentReadPermission(const UserId& user_id, const DepartmentId& department_id) const override;

private:
    std::optional<Permissions> getUserDepartmentPermissions(const UserId& user_id,
                                                            const DepartmentId& department_id) const;

private:
    std::shared_ptr<PermissionRepositoryInterface> permission_repository_;
};

}  // namespace domain
