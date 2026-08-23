#pragma once

#include <optional>

#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/shop.h"

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
