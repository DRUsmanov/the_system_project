#include "factories_impl/permission_service_factory_impl/permission_service_factory_impl.h"

#include "repositories_impl/permission_repository/permission_repository.h"
#include "services/permission_service/permission_service.h"

using namespace infrastructure;

std::shared_ptr<application::PermissionServiceInterface> PermissionServiceFactory::createPermissionService(
    std::shared_ptr<application::UowInterface> uow) const {
    auto permission_repository =
        std::make_shared<PermissionRepository>(std::shared_ptr<Uow>(dynamic_cast<Uow*>(uow.get())));
    return std::make_shared<application::PermissionService>(permission_repository);
}
