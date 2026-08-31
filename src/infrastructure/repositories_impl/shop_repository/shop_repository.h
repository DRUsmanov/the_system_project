#pragma once

#include "domain/repositories/shop_repository_interface.h"
#include "infrastructure/uow_impl/uow_impl.h"

namespace infrastructure {

class ShopRepository : public domain::ShopRepositoryInterface {
public:
    ShopRepository(std::shared_ptr<Uow> uow) : uow_{uow} {}

    domain::Shop downloadShop() const override;
    bool uploadEmployee(const domain::Employee& employee,
                        domain::DepartmentId department_id,
                        domain::StaffPositionId staff_position_id,
                        domain::WorkScheduleId work_schedule_id) override;

private:
    std::shared_ptr<Uow> uow_;
};

}  // namespace infrastructure
