#pragma once

#include "shop_service_interface.h"

#include <chrono>

namespace application{

class ShopService : public ShopServiceInterface {
public:
    ShopService(domain::ShopRepositoryInterface& shop_repository)
    : ShopServiceInterface{shop_repository} { }

    domain::Shop GetShop() const override;
};

} // namespace application

