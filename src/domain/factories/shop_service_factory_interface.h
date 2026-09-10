#pragma once

#include <memory>

#include "services/shop_service/shop_service_interface.h"
#include "uow/uow_interface.h"

namespace domain {

class ShopServiceFactoryInterface {
public:
    virtual ~ShopServiceFactoryInterface() = default;

    virtual std::shared_ptr<ShopServiceInterface> createShopService(std::shared_ptr<UowInterface> uow) const = 0;
};

}  // namespace domain
