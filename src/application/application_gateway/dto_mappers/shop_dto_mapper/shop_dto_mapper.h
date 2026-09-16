#pragma once

#include "application_gateway/dto_mappers/shop_dto_mapper/shop_dto_mapper_interface.h"

namespace application {

class ShopDtoMapper : public ShopDtoMapperInterface {
public:
    // ADD EMPLOYEE
    std::pair<domain::EmployeeAssignment, domain::Employee> convert(
        const AddEmployeeRequestDto& add_employee_request_dto) const override;
    AddEmployeeResponseDto convert(domain::EmployeeId employee_id) const override;

    // REMOVE EMPLOYEE
    std::pair<domain::EmployeeId, domain::Date> convert(
        const RemoveEmployeeRequestDto& remove_employee_request_dto) const override;

    // GET DEPARTMENTS
    GetDepartmentsResponseDto convert(const domain::Departments& departments) const override;

    // GET STAFF POSITIONS
    GetStaffPositionsResponseDto convert(const domain::StaffPositions& staff_positions) const override;

    // GET DEPARTMENTS STAFF
    domain::DepartmentId convert(const GetDepartmentStaffRequestDto& get_department_staff_request_dto) const override;
    GetDepartmentStaffResponseDto convert(const domain::Staff& department_staff) const override;

    // UPDATE EMPLOYEE
    std::tuple<domain::EmployeeId, domain::Employee, domain::EmployeeAssignment, std::optional<domain::Date>> convert(
        const UpdateEmployeeRequestDto& update_employee_request_dto) const override;
};

}  // namespace application
