#pragma once

#include "application/dto/shop_dto.h"
#include "domain/entities/shop/department/department.h"
#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/shop.h"

namespace application {

class ShopDtoMapperInterface {
public:
    virtual ~ShopDtoMapperInterface() = default;

    virtual std::pair<domain::Shop::EmployeeAssignment, domain::Employee> convert(
        const AddEmployeeInputDto& add_employee_input_dto) const = 0;
};

}  // namespace application
