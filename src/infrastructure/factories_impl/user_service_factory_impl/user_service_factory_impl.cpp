#include "user_service_factory_impl.h"

#include "repositories_impl/user_repository/user_repository.h"
#include "services/user_service/user_service.h"

namespace infrastructure {

std::shared_ptr<application::UserServiceInterface> UserServiceFactory::createUserService(
    std::shared_ptr<application::UowInterface> uow) const {
    auto user_repository = std::make_shared<UserRepository>(std::shared_ptr<Uow>(dynamic_cast<Uow*>(uow.get())));
    return std::make_shared<application::UserService>(user_repository);
}

}  // namespace infrastructure
