#pragma once

#include <chrono>
#include <memory>

#include "domain/interfaces/repositorys/shop_repository_interface.h"
#include "shop_service_interface.h"

namespace application {

class ShopService : public ShopServiceInterface {
public:
    ShopService(std::shared_ptr<domain::ShopRepositoryInterface> shop_repository) : shop_repository_{shop_repository} {}

    domain::Shop getShop() const override;
    bool addEmployee(domain::Shop::EmployeeAssignment employee_assignment, const domain::Employee& employee) override;

private:
    std::shared_ptr<domain::ShopRepositoryInterface> shop_repository_;
};

}  // namespace application
