#include "shop_service_factory.h"

#include "repositories_impl/shop_repository/shop_repository.h"
#include "services/shop_service/shop_service.h"

using namespace infrastructure;

std::shared_ptr<application::ShopServiceInterface> ShopServiceFactory::createShopService(
    std::shared_ptr<application::UowInterface> uow) const {
    auto shop_repository = std::make_shared<ShopRepository>(std::shared_ptr<Uow>(dynamic_cast<Uow*>(uow.get())));
    return std::make_shared<application::ShopService>(shop_repository);
}
