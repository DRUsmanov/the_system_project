#pragma once

#include "shop_dto_mapper_interface.h"

namespace application {

class ShopDtoMapper : public ShopDtoMapperInterface {
public:
    std::pair<domain::DepartmentId, domain::Employee> convert(
        const AddEmployeeInputDto& add_employee_input_dto) const override;
};

}  // namespace application
