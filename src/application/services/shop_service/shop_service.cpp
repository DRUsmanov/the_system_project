#include "shop_service.h"

domain::Shop application::ShopService::GetShop() const {
    return shop_repository_.LoadShop();
}