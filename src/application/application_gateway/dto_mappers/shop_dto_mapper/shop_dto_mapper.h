#pragma once

#include "shop_dto_mapper_interface.h"

namespace application {

class ShopDtoMapper : public ShopDtoMapperInterface {
public:
    std::pair<domain::Shop::EmployeeAssignment, domain::Employee> convert(
        const AddEmployeeRequestDto& add_employee_request_dto) const override;
};

}  // namespace application
