#include "employee_dto_mapper.h"
#include "domain/value_data/types.h"

using namespace application;

domain::Employee EmployeeDtoMapper::Convert(const AddEmployeeInputDto& add_employee_input_dto) const {
    domain::Employee employee;
    employee.last_name = add_employee_input_dto.last_name;
    employee.first_name = add_employee_input_dto.first_name;
    employee.patronymic = add_employee_input_dto.patronymic;
    employee.birth_date = domain::DateFromString(add_employee_input_dto.birth_date);
    employee.employment_date = domain::DateFromString(add_employee_input_dto.employment_date);
    employee.employee_number = add_employee_input_dto.employee_number;
    return employee;
}