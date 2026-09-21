#include "application_gateway/dto_mappers/shop_dto_mapper/shop_dto_mapper.h"

#include <cassert>

#include "value_data/types.h"

using namespace application;

// ======================================================================
// ADD EMPLOYEE
// ======================================================================

std::pair<domain::EmployeeAssignment, domain::Employee> ShopDtoMapper::convert(
    const AddEmployeeRequestDto& add_employee_request_dto) const {
    domain::EmployeeAssignment employee_assignment;
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

std::pair<domain::EmployeeId, domain::Date> ShopDtoMapper::convert(
    const RemoveEmployeeRequestDto& remove_employee_request_dto) const {
    auto empployee_id = domain::EmployeeId{remove_employee_request_dto.employee_id};
    auto removing_date = domain::dateFromString(remove_employee_request_dto.removing_date);
    return {empployee_id, removing_date};
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
    for (const auto& [staff_position_id, staff_position] : staff_positions) {
        get_staff_positions_response_dto.staff_positions[*staff_position_id] = staff_position.description;
    }
    return get_staff_positions_response_dto;
}

domain::DepartmentId ShopDtoMapper::convert(
    const GetDepartmentStaffRequestDto& get_department_staff_request_dto) const {
    return domain::DepartmentId{get_department_staff_request_dto.department_id};
}

GetDepartmentStaffResponseDto ShopDtoMapper::convert(const domain::Staff& department_staff) const {
    GetDepartmentStaffResponseDto get_department_staff_response_dto;
    const auto& employees = department_staff.getEmployees();
    const auto& employee_assignments = department_staff.getEmployeeAssignments();

    assert(employees.size() == employee_assignments.size());  // проверка в дебаг сборке

    for (const auto& [employee_id, employee] : employees) {
        GetDepartmentStaffResponseDto::Data data;

        data.employee_id = *employee_id;
        data.last_name = employee.last_name;
        data.first_name = employee.first_name;
        data.patronymic = employee.patronymic;
        data.birth_date = domain::dateToString(employee.birth_date);
        data.employment_date = domain::dateToString(employee.employment_date);
        data.employee_number = employee.employee_number;
        data.department_id = *employee_assignments.at(employee_id).department_id;
        data.staff_position_id = *employee_assignments.at(employee_id).staff_position_id;
        data.work_schedule_id = *employee_assignments.at(employee_id).work_schedule_id;

        get_department_staff_response_dto.data.push_back(data);
    }

    return get_department_staff_response_dto;
}

std::tuple<domain::EmployeeId, domain::Employee, domain::EmployeeAssignment, std::optional<domain::Date>>
application::ShopDtoMapper::convert(const UpdateEmployeeRequestDto& update_employee_request_dto) const {
    domain::EmployeeId employee_id{update_employee_request_dto.employee_id};

    domain::Employee employee;
    employee.last_name = update_employee_request_dto.last_name;
    employee.first_name = update_employee_request_dto.first_name;
    employee.patronymic = update_employee_request_dto.patronymic;
    employee.birth_date = domain::dateFromString(update_employee_request_dto.birth_date);
    employee.employment_date = domain::dateFromString(update_employee_request_dto.employment_date);
    employee.employee_number = update_employee_request_dto.employee_number;

    domain::DepartmentId department_id{update_employee_request_dto.department_id};
    domain::StaffPositionId staff_position_id{update_employee_request_dto.staff_position_id};
    domain::WorkScheduleId work_schedule_id{update_employee_request_dto.work_schedule_id};
    domain::EmployeeAssignment employee_assignment;
    employee_assignment.department_id = department_id;
    employee_assignment.staff_position_id = staff_position_id;
    employee_assignment.work_schedule_id = work_schedule_id;

    std::optional<domain::Date> assignment_changing_date = std::nullopt;

    if (update_employee_request_dto.assignment_changing_date.has_value()) {
        assignment_changing_date = domain::dateFromString(update_employee_request_dto.assignment_changing_date.value());
    }

    return {employee_id, employee, employee_assignment, assignment_changing_date};
}
