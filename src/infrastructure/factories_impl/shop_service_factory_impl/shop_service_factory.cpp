#include "shop_service_factory.h"

#include "application/services/shop_service/shop_service.h"
#include "infrastructure/repositorys_impl/shop_repository/shop_repository.h"

using namespace infrastructure;

std::shared_ptr<application::ShopServiceInterface> ShopServiceFactory::createShopService(
    std::shared_ptr<application::UowInterface> uow) const {
    auto shop_repository = std::make_shared<ShopRepository>(uow);
    return std::make_shared<application::ShopService>(shop_repository);
}
