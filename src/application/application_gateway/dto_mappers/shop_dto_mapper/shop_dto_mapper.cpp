#include "application_gateway/dto_mappers/shop_dto_mapper/shop_dto_mapper.h"

#include "value_data/types.h"

using namespace application;

// ======================================================================
// ADD EMPLOYEE
// ======================================================================

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

AddEmployeeResponseDto ShopDtoMapper::convert(domain::EmployeeId employee_id) const {
    AddEmployeeResponseDto add_employee_response_dto;
    add_employee_response_dto.employee_id = *employee_id;
    return add_employee_response_dto;
}

// ======================================================================
// REMOVE EMPLOYEE
// ======================================================================

domain::EmployeeId ShopDtoMapper::convert(const RemoveEmployeeRequestDto& remove_employee_request_dto) const {
    return domain::EmployeeId{remove_employee_request_dto.employee_id};
}

RemoveEmployeeResponseDto application::ShopDtoMapper::convert(bool is_employee_removed) const {
    return RemoveEmployeeResponseDto{is_employee_removed};
}

// ======================================================================
// GET DEPARTMENTS
// ======================================================================

GetDepartmentsResponseDto ShopDtoMapper::convert(const domain::Departments& departments) const {
    GetDepartmentsResponseDto get_departments_response_dto;
    for (const auto& department : departments) {
        get_departments_response_dto.departmens[*department.department_id] = department.description;
    }
    return get_departments_response_dto;
}

// ======================================================================
// GET STAFF POSITIONS
// ======================================================================

GetStaffPositionsResponseDto ShopDtoMapper::convert(const domain::StaffPositions& staff_positions) const {
    GetStaffPositionsResponseDto get_staff_positions_response_dto;
    for (const auto& staff_position : staff_positions) {
        get_staff_positions_response_dto.staff_positions[*staff_position.staff_position_id] =
            staff_position.description;
    }
    return get_staff_positions_response_dto;
}
