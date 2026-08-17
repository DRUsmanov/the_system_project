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
    bool addEmployee(const domain::Employee& employee,
                     domain::DepartmentId department_id,
                     domain::StaffPositionId staff_position_id,
                     domain::WorkScheduleId work_schedule_id) override;

private:
    std::shared_ptr<domain::ShopRepositoryInterface> shop_repository_;
};

}  // namespace application
