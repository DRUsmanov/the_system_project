#include "permission_service_factory_impl.h"

#include "application/services/permission_service/permission_service.h"
#include "infrastructure/repositorys_impl/permission_repository/permission_repository.h"

using namespace infrastructure;

std::shared_ptr<application::PermissionServiceInterface> PermissionServiceFactory::createPermissionService(
    std::shared_ptr<application::UowInterface> uow) const {
    auto permission_repository = std::make_shared<PermissionRepository>(uow);
    return std::make_shared<application::PermissionService>(permission_repository);
}
