#pragma once

#include "factories/shop_service_factory_interface.h"

namespace infrastructure {

class ShopServiceFactory : public domain::ShopServiceFactoryInterface {
public:
    std::shared_ptr<domain::ShopServiceInterface> createShopService(
        std::shared_ptr<domain::UowInterface> uow) const override;
};

}  // namespace infrastructure
