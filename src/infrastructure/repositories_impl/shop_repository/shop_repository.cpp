#include "repositories_impl/shop_repository/shop_repository.h"

#include <cstdint>

#include "connection_pool/querys.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/profession/profession.h"
#include "logger.h"

using namespace infrastructure;

domain::EmployeeAssignments ShopRepository::downloadAllEmployeeAssignments() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return domain::EmployeeAssignments();
    // TODO
}

std::optional<domain::EmployeeId> ShopRepository::uploadEmployee(const domain::Employee& employee,
                                                                 domain::DepartmentId department_id,
                                                                 domain::StaffPositionId staff_position_id,
                                                                 domain::WorkScheduleId work_schedule_id) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_EMPLOYEE_BY_EMPLOYEE_NUMBER, employee.employee_number);

    if (result.size() > 0) {
        return std::nullopt;
    }

    result = uow_->execParams(query::UPLOAD_EMPLOYEE,
                              employee.last_name,
                              employee.first_name,
                              employee.patronymic,
                              domain::dateToString(employee.birth_date),
                              domain::dateToString(employee.employment_date),
                              employee.employee_number);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::EmployeeId employee_id{result.at(0).at(tables::employees::ID).as<uint64_t>()};

    result = uow_->execParams(query::UPLOAD_EMPLOYEE_ASSIGNMENT,
                              *employee_id,
                              *department_id,
                              *staff_position_id,
                              *work_schedule_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    result = uow_->execParams(query::DOWNLOAD_STAFF_POSITION, *staff_position_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::ProfessionId professions_id{result.at(0).at(tables::staff_positions::DEFAULT_PROFESSION_ID).as<uint64_t>()};

    result = uow_->execParams(query::UPLOAD_EMPLOYEE_PROFESSIONS, *employee_id, *professions_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    return employee_id;
}

std::optional<domain::Employee> ShopRepository::downloadEmployee(domain::EmployeeId employee_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_EMPLOYEE_BY_EMPLOYEE_ID, *employee_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    std::string last_name{result.at(0).at(tables::employees::LAST_NAME).as<std::string>()};
    std::string first_name{result.at(0).at(tables::employees::FIRST_NAME).as<std::string>()};
    std::string patronymic{result.at(0).at(tables::employees::PATRONYMIC).as<std::string>()};
    domain::Date birth_date{domain::dateFromString(result.at(0).at(tables::employees::BIRTH_DATE).as<std::string>())};
    domain::Date employment_date{
        domain::dateFromString(result.at(0).at(tables::employees::EMPLOYMENT_DATE).as<std::string>())};
    domain::EmployeeNumber employee_number{result.at(0).at(tables::employees::EMPLOYEE_NUMBER).as<uint64_t>()};

    domain::Employee employee;
    employee.employee_id = employee_id;
    employee.last_name = last_name;
    employee.first_name = first_name;
    employee.patronymic = patronymic;
    employee.birth_date = birth_date;
    employee.employment_date = employment_date;
    employee.employee_number = employee_number;

    return employee;
}

std::optional<domain::EmployeeAssignment> ShopRepository::downloadEmployeeAssignment(
    domain::EmployeeId employee_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_EMPLOYEE_ASSIGNMENT, *employee_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::DepartmentId department_id{result.at(0).at(tables::staffing_assignments::DEPARTMENT_ID).as<uint64_t>()};
    domain::StaffPositionId staff_position_id{
        result.at(0).at(tables::staffing_assignments::STAFF_POSITION_ID).as<uint64_t>()};
    domain::WorkScheduleId work_schedule_id{
        result.at(0).at(tables::staffing_assignments::WORK_SCHEDULE_ID).as<uint64_t>()};

    domain::EmployeeAssignment employee_assignment;
    employee_assignment.department_id = department_id;
    employee_assignment.staff_position_id = staff_position_id;
    employee_assignment.work_schedule_id = work_schedule_id;

    return employee_assignment;
}

bool infrastructure::ShopRepository::removeEmployee(domain::EmployeeId employee_id) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::REMOVE_EMPLOYEE, *employee_id);
    return result.affected_rows() == 1;
}

std::optional<domain::Departments> infrastructure::ShopRepository::downloadDepartments() const {
    auto result = uow_->execParams(query::DOWNLOAD_DEPARTMENTS);
    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::Departments departments;

    for (const auto& row : result) {
        domain::DepartmentId department_id{row.at(tables::departments::ID).as<uint64_t>()};
        std::string description{row.at(tables::departments::DESCRIPTION).as<std::string>()};

        departments.push_back({department_id, description});
    }

    return departments;
}

std::optional<domain::StaffPositions> infrastructure::ShopRepository::downloadStaffPositions() const {
    auto result = uow_->execParams(query::DOWNLOAD_STAFF_POSITIONS);
    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::StaffPositions staff_positions;

    for (const auto& row : result) {
        domain::StaffPositionId staff_position_id{row.at(tables::departments::ID).as<uint64_t>()};
        std::string description{row.at(tables::departments::DESCRIPTION).as<std::string>()};
        domain::ProfessionId default_profession_id{
            row.at(tables::staff_positions::DEFAULT_PROFESSION_ID).as<uint64_t>()};

        domain::StaffPosition staff_position;

        staff_position.staff_position_id = staff_position_id;
        staff_position.description = description;
        staff_position.default_profession_id = default_profession_id;

        staff_positions.push_back(staff_position);
    }

    return staff_positions;
}
