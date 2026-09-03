#pragma once

#include "factories/permission_service_factory_interface.h"

namespace infrastructure {

class PermissionServiceFactory : public application::PermissionServiceFactoryInterface {
public:
    std::shared_ptr<application::PermissionServiceInterface> createPermissionService(
        std::shared_ptr<application::UowInterface> uow) const override;
};

}  // namespace infrastructure
