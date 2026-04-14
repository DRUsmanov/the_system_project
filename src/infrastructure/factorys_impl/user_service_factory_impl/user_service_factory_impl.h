#pragma once

#include "application/factorys/user_service_factory_interface.h"

namespace infrastructure {

class UserServiceFactory : application::UserServiceFactoryInterface {
public:
    std::shared_ptr<application::UserServiceInterface> CreateUserService(std::shared_ptr<application::UowInterface> uow) const override;
};
    
} // namespace infrastructure
