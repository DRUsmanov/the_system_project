#pragma once

#include "application_gateway/dto/shop_dto.h"
#include "entities/shop/department/department.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/shop.h"

namespace application {

class ShopDtoMapperInterface {
public:
    virtual ~ShopDtoMapperInterface() = default;

    virtual std::pair<domain::Shop::EmployeeAssignment, domain::Employee> convert(
        const AddEmployeeRequestDto& add_employee_request_dto) const = 0;
};

}  // namespace application
