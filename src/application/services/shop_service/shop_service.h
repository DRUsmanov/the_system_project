#pragma once

#include "shop_service_interface.h"
#include "domain/interfaces/repositorys/shop_repository_interface.h"

#include <chrono>
#include <memory>

namespace application{

class ShopService : public ShopServiceInterface {
public:
    ShopService(std::shared_ptr<domain::ShopRepositoryInterface> shop_repository)
    : shop_repository_{shop_repository} { }

    domain::Shop GetShop() const override;

private:
    std::shared_ptr<domain::ShopRepositoryInterface> shop_repository_;
};

} // namespace application

