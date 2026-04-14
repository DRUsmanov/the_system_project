#pragma once

#include "domain/entities/shop/shop.h"

#include <chrono>

namespace application{

class ShopServiceInterface{
public:
    virtual ~ShopServiceInterface() = default;

    virtual domain::Shop GetShop() const = 0; // Далее можно добавить перегрузки с id при расширении программы
};

} // namespace application

