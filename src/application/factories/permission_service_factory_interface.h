#pragma once

#include <memory>

#include "services/permission_service/permission_service_interface.h"
#include "uow/uow_interface.h"

namespace application {

class PermissionServiceFactoryInterface {
public:
    virtual ~PermissionServiceFactoryInterface() = default;

    virtual std::shared_ptr<PermissionServiceInterface> createPermissionService(
        std::shared_ptr<UowInterface> uow) const = 0;
};

}  // namespace application
