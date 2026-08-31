#pragma once

#include "application/factories/shop_service_factory_interface.h"

namespace infrastructure {

class ShopServiceFactory : public application::ShopServiceFactoryInterface {
public:
    std::shared_ptr<application::ShopServiceInterface> createShopService(
        std::shared_ptr<application::UowInterface> uow) const override;
};

}  // namespace infrastructure
