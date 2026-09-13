#pragma once

#include <vector>

#include "application_gateway/dto/shop_dto.h"
#include "entities/shop/department/department.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/employee_assignments/employee_assignments.h"
#include "entities/shop/staff/staff.h"

namespace application {

class ShopDtoMapperInterface {
public:
    virtual ~ShopDtoMapperInterface() = default;

    // ADD EMPLOYEE
    virtual std::pair<domain::EmployeeAssignment, domain::Employee> convert(
        const AddEmployeeRequestDto& add_employee_request_dto) const = 0;
    virtual AddEmployeeResponseDto convert(domain::EmployeeId employee_id) const = 0;

    // REMOVE EMPLOYEE
    virtual domain::EmployeeId convert(const RemoveEmployeeRequestDto& remove_employee_request_dto) const = 0;

    // GET DEPARTMENTS
    virtual GetDepartmentsResponseDto convert(const domain::Departments& departments) const = 0;

    // GET STAFF POSITIONS
    virtual GetStaffPositionsResponseDto convert(const domain::StaffPositions& staff_positions) const = 0;

    // GET DEPARTMENTS STAFF
    virtual domain::DepartmentId convert(
        const GetDepartmentStaffRequestDto& get_department_staff_request_dto) const = 0;
    virtual GetDepartmentStaffResponseDto convert(const domain::Staff& department_staff) const = 0;

    // UPDATE EMPLOYEE
    virtual std::tuple<domain::EmployeeId, domain::Employee, domain::EmployeeAssignment> convert(
        const UpdateEmployeeRequestDto& update_employee_request_dto) const = 0;
};

}  // namespace application
