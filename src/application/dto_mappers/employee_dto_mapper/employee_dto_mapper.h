#pragma once

#include "employee_dto_mapper_interface.h"

namespace application {

class EmployeeDtoMapper : public  EmployeeDtoMapperInterface{
public:
    domain::Employee Convert(const AddEmployeeInputDto& add_employee_input_dto) const override;
};
    
} // namespace application
