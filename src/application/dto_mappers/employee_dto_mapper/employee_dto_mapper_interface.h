#pragma once

#include "application/dto/employee_dto.h"
#include "domain/entities/shop/employee/employee.h"

namespace application {

class EmployeeDtoMapperInterface {
public:
    virtual ~EmployeeDtoMapperInterface() = default;

    virtual domain::Employee Convert(const AddEmployeeInputDto& add_employee_input_dto) const = 0;
};
    
} // namespace application
