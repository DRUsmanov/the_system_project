#pragma once

#include "domain/entities/shop/shop.h"
#include "domain/interfaces/repositorys/shop_repository.h"

#include <chrono>

namespace application{

class ShopService{
public:
    ShopService(domain::ShopRepositoryInterface& shop_repository)
    : shop_repository_{shop_repository} { }

    domain::Shop GetShop() const;
private:
    domain::ShopRepositoryInterface& shop_repository_;
};

} // namespace application

