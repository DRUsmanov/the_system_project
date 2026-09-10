#pragma once

#include <memory>

#include "services/user_service/user_service_interface.h"
#include "uow/uow_interface.h"

namespace domain {

class UserServiceFactoryInterface {
public:
    virtual std::shared_ptr<UserServiceInterface> createUserService(std::shared_ptr<UowInterface> uow) const = 0;
};

}  // namespace domain
