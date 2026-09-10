#pragma once

#include "factories/user_service_factory_interface.h"

namespace infrastructure {

class UserServiceFactory : public domain::UserServiceFactoryInterface {
public:
    std::shared_ptr<domain::UserServiceInterface> createUserService(
        std::shared_ptr<domain::UowInterface> uow) const override;
};

}  // namespace infrastructure
