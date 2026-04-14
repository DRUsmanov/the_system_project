#include "user_service_factory_impl.h"
#include "application/services/user_service/user_service.h"
#include "infrastructure/repositorys_impl/user_repository/user_repository.h"

namespace infrastructure {

std::shared_ptr<application::UserServiceInterface> UserServiceFactory::CreateUserService(std::shared_ptr<application::UowInterface> uow) const {
    auto user_repository = std::make_shared<UserRepository>(uow);
    return std::make_shared<application::UserService>(user_repository);
}
    
} // namespace infrastructure


