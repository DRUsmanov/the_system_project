#include "shop_dto_mapper.h"

#include "domain/value_data/types.h"

using namespace application;

std::pair<domain::Shop::EmployeeAssignment, domain::Employee> ShopDtoMapper::convert(
    const AddEmployeeRequestDto& add_employee_request_dto) const {
    domain::Shop::EmployeeAssignment employee_assignment;
    employee_assignment.department_id = domain::DepartmentId{add_employee_request_dto.department_id};
    employee_assignment.staff_position_id = domain::StaffPositionId{add_employee_request_dto.staff_position_id};
    employee_assignment.work_schedule_id = domain::WorkScheduleId{add_employee_request_dto.work_schedule_id};

    domain::Employee employee;
    employee.last_name = add_employee_request_dto.last_name;
    employee.first_name = add_employee_request_dto.first_name;
    employee.patronymic = add_employee_request_dto.patronymic;
    employee.birth_date = domain::dateFromString(add_employee_request_dto.birth_date);
    employee.employment_date = domain::dateFromString(add_employee_request_dto.employment_date);
    employee.employee_number = add_employee_request_dto.employee_number;
    return {employee_assignment, employee};
}