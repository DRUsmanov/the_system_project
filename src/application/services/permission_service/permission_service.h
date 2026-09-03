#pragma once

#include <chrono>
#include <memory>

#include "repositories/permission_repository_interface.h"
#include "services/permission_service/permission_service_interface.h"

namespace application {

class PermissionService : public PermissionServiceInterface {
public:
    PermissionService(std::shared_ptr<domain::PermissionRepositoryInterface> permission_repository) :
        permission_repository_{permission_repository} {}

    bool checkUserDepartmentWritePermission(const domain::UserId& user_id,
                                            const domain::DepartmentId& department_id) const override;
    bool checkUserDepartmentReadPermission(const domain::UserId& user_id,
                                           const domain::DepartmentId& department_id) const override;

private:
    std::optional<domain::Permissions> getUserDepartmentPermissions(const domain::UserId& user_id,
                                                                    const domain::DepartmentId& department_id) const;

private:
    std::shared_ptr<domain::PermissionRepositoryInterface> permission_repository_;
};

}  // namespace application
