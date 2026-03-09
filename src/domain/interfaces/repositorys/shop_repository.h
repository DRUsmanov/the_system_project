#pragma once

#include "domain/entities/shop/shop.h"

namespace domain {

class ShopRepositoryInterface {
public:
    virtual ~ShopRepositoryInterface() = default;

    virtual Shop GetShop() const = 0;
};
    
} // namespace domai 
