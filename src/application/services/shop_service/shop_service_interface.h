#pragma once

#include "domain/entities/shop/shop.h"
#include "domain/interfaces/repositorys/shop_repository_interface.h"

#include <chrono>

namespace application{

class ShopServiceInterface{
public:
    ShopServiceInterface(domain::ShopRepositoryInterface& shop_repository)
    : shop_repository_{shop_repository} { }

    virtual ~ShopServiceInterface() = default;

    

    virtual domain::Shop GetShop() const = 0; // Далее можно добавить перегрузки с id при расширении программы
protected:
    domain::ShopRepositoryInterface& shop_repository_;
};

} // namespace application

