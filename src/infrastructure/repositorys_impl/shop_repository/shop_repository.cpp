#include "shop_repository.h"

#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/shop/profession/profession.h"
#include "infrastructure/connection_pool/querys.h"

using namespace infrastructure;

bool ShopRepository::uploadEmployee(const domain::Employee& employee,
                                    domain::DepartmentId department_id,
                                    domain::StaffPositionId staff_position_id,
                                    domain::WorkScheduleId work_schedule_id) {
    pqxx::work work(uow_->getConnection());

    auto result = work.exec_params(query::UPLOAD_EMPLOYEE,
                                   employee.last_name,
                                   employee.first_name,
                                   employee.patronymic,
                                   employee.birth_date,
                                   employee.employment_date,
                                   employee.employee_number);

    if (result.size() != 1) {
        return false;
    }

    domain::EmployeeId employee_id = result[0][0].as<domain::EmployeeId>();

    result = work.exec_params(query::UPLOAD_EMPLOYEE_ASSIGNMENT,
                              employee_id,
                              department_id,
                              staff_position_id,
                              work_schedule_id);

    if (result.size() != 1) {
        return false;
    }

    result = work.exec_params(query::DOWNLOAD_DEFAULT_PROFESSION, staff_position_id);

    if (result.size() != 1) {
        return false;
    }

    domain::ProfessionId professions_id = result[0][0].as<domain::ProfessionId>();

    result = work.exec_params(query::UPLOAD_EMPLOYEE_PROFESSIONS, employee_id, professions_id);

    if (result.size() != 1) {
        return false;
    }

    return true;
}
