#pragma once

#include <chrono>
#include <optional>

#include "entities/shop/employee/employee.h"
#include "entities/shop/shop.h"

namespace domain {

class ShopServiceInterface {
public:
    virtual ~ShopServiceInterface() = default;

    virtual Shop getShop() const = 0;
    virtual std::optional<EmployeeId> addNewEmployee(Shop::EmployeeAssignment employee_assignment,
                                                     const Employee& employee) = 0;
};

}  // namespace domain
