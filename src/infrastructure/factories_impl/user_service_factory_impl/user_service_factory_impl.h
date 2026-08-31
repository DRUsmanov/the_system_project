#pragma once

#include "application/factories/user_service_factory_interface.h"

namespace infrastructure {

class UserServiceFactory : public application::UserServiceFactoryInterface {
public:
    std::shared_ptr<application::UserServiceInterface> createUserService(
        std::shared_ptr<application::UowInterface> uow) const override;
};

}  // namespace infrastructure
