#include "factories_impl/permission_service_factory_impl/permission_service_factory_impl.h"

#include "logger.h"
#include "repositories_impl/permission_repository/permission_repository.h"
#include "services/permission_service/permission_service.h"

using namespace infrastructure;

std::shared_ptr<application::PermissionServiceInterface> PermissionServiceFactory::createPermissionService(
    std::shared_ptr<application::UowInterface> uow) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto permission_repository = std::make_shared<PermissionRepository>(std::dynamic_pointer_cast<Uow>(uow));
    return std::make_shared<application::PermissionService>(permission_repository);
}
