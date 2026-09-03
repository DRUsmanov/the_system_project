#include "repositories_impl/shop_repository/shop_repository.h"

#include <cstdint>

#include "connection_pool/querys.h"
#include "entities/shop/employee/employee.h"
#include "entities/shop/profession/profession.h"

using namespace infrastructure;

domain::Shop infrastructure::ShopRepository::downloadShop() const {
    return domain::Shop();
}

bool ShopRepository::uploadEmployee(const domain::Employee& employee,
                                    domain::DepartmentId department_id,
                                    domain::StaffPositionId staff_position_id,
                                    domain::WorkScheduleId work_schedule_id) {
    auto result = uow_->execParams(query::UPLOAD_EMPLOYEE,
                                   employee.last_name,
                                   employee.first_name,
                                   employee.patronymic,
                                   domain::dateToString(employee.birth_date),
                                   domain::dateToString(employee.employment_date),
                                   employee.employee_number);

    if (result.size() != 1) {
        return false;
    }

    domain::EmployeeId employee_id{result[0][0].as<uint64_t>()};

    result = uow_->execParams(query::UPLOAD_EMPLOYEE_ASSIGNMENT,
                              *employee_id,
                              *department_id,
                              *staff_position_id,
                              *work_schedule_id);

    if (result.size() != 1) {
        return false;
    }

    result = uow_->execParams(query::DOWNLOAD_DEFAULT_PROFESSION, *staff_position_id);

    if (result.size() != 1) {
        return false;
    }

    domain::ProfessionId professions_id{result[0][0].as<uint64_t>()};

    result = uow_->execParams(query::UPLOAD_EMPLOYEE_PROFESSIONS, *employee_id, *professions_id);

    if (result.size() != 1) {
        return false;
    }

    return true;
}
