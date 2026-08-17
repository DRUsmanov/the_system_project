#pragma once

#include <memory>

#include "application/services/user_service/user_service_interface.h"
#include "application/uow/uow_interface.h"

namespace application {

class UserServiceFactoryInterface {
public:
    virtual std::shared_ptr<UserServiceInterface> createUserService(std::shared_ptr<UowInterface> uow) const = 0;
};

}  // namespace application
