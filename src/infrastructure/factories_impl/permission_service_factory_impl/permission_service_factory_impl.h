#pragma once

#include "factories/permission_service_factory_interface.h"

namespace infrastructure {

class PermissionServiceFactory : public domain::PermissionServiceFactoryInterface {
public:
    std::shared_ptr<domain::PermissionServiceInterface> createPermissionService(
        std::shared_ptr<domain::UowInterface> uow) const override;
};

}  // namespace infrastructure
