#include "shop_service.h"

using namespace application;

domain::Shop ShopService::GetShop() const {
    return shop_repository_->LoadShop();
}