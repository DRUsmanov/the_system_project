#include "repositories_impl/shop_repository/shop_repository.h"

#include <cstdint>

#include "connection_pool/querys.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/profession/profession.h"
#include "logger.h"

using namespace infrastructure;

domain::Shop ShopRepository::downloadShop() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return domain::Shop();
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

    result = uow_->execParams(query::DOWNLOAD_DEFAULT_PROFESSION, *staff_position_id);

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

    if (result.size() > 0) {
        return std::nullopt;
    }

    domain::Employee employee;
    // TODO: пока в ней нет необходимости
    return std::nullopt;
}
