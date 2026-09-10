#pragma once

#include "application_gateway/dto_mappers/shop_dto_mapper/shop_dto_mapper_interface.h"

namespace application {

class ShopDtoMapper : public ShopDtoMapperInterface {
public:
    std::pair<domain::Shop::EmployeeAssignment, domain::Employee> convert(
        const AddEmployeeRequestDto& add_employee_request_dto) const override;
    AddEmployeeResponseDto convert(domain::EmployeeId employee_id) const override;

public:
    domain::EmployeeId convert(const RemoveEmployeeRequestDto& remove_employee_request_dto) const override;
    RemoveEmployeeResponseDto convert(bool is_employee_removed) const override;
};

}  // namespace application
