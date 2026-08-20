#pragma once

#include <chrono>
#include <memory>

#include "domain/interfaces/repositorys/permission_repository_interface.h"
#include "permission_service_interface.h"

namespace application {

class PermissionService : public PermissionServiceInterface {
public:
    PermissionService(std::shared_ptr<domain::PermissionRepositoryInterface> permission_repository) :
        permission_repository_{permission_repository} {}

    bool checkUserAddEmployeeToDepartmentPermission(const domain::UserId& user_id,
                                                    const domain::DepartmentId& department_id) const override;

private:
    std::shared_ptr<domain::PermissionRepositoryInterface> permission_repository_;
};

}  // namespace application
