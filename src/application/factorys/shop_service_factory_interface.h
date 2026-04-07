#pragma once

#include "application/services/shop_service/shop_service_interface.h"
#include "application/uow/uow_interface.h"

#include <memory>

namespace application {

class ShopServiceFactoryInterface {
public:
    virtual ~ShopServiceFactoryInterface() = default;

    virtual std::shared_ptr<ShopServiceInterface> CreateShopService(std::shared_ptr<UowInterface> uow) const = 0;
};
    
} // namespace application


