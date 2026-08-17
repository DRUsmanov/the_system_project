#pragma once

#include <chrono>

#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/shop.h"

namespace application {

class ShopServiceInterface {
public:
    virtual ~ShopServiceInterface() = default;

    virtual domain::Shop getShop() const = 0;
    virtual bool addEmployee(const domain::Employee& employee,
                             domain::DepartmentId department_id,
                             domain::StaffPositionId staff_position_id,
                             domain::WorkScheduleId work_schedule_id) = 0;
};

}  // namespace application
