#pragma once

#include <chrono>
#include <optional>

#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/shop.h"

namespace application {

class ShopServiceInterface {
public:
    virtual ~ShopServiceInterface() = default;

    virtual domain::Shop getShop() const = 0;
    virtual bool addNewEmployee(domain::Shop::EmployeeAssignment employee_assignment,
                                const domain::Employee& employee) = 0;
};

}  // namespace application
