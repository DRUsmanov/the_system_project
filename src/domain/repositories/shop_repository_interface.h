#pragma once

#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/shop.h"

namespace domain {

class ShopRepositoryInterface {
public:
    virtual ~ShopRepositoryInterface() = default;

    virtual Shop downloadShop() const = 0;
    virtual bool uploadEmployee(const domain::Employee& employee,
                                domain::DepartmentId department_id,
                                domain::StaffPositionId staff_position_id,
                                domain::WorkScheduleId work_schedule_id) = 0;
};

}  // namespace domain
