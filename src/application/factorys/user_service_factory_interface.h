#pragma once

#include "application/services/user_service/user_service_interface.h"
#include "application/uow/uow_interface.h"

#include <memory>

namespace application {

class UserServiceFactoryInterface {
public:
    virtual std::shared_ptr<UserServiceInterface> CreateUserService(std::shared_ptr<UowInterface> uow) const = 0;
};
    
} // namespace application


