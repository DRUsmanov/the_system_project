#include "employee_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {

constexpr std::string_view LAST_NAME{"last_name"};
constexpr std::string_view FIRST_NAME{"first_name"};
constexpr std::string_view PATRONYMIC{"patronymic"};
constexpr std::string_view BIRTH_DATE{"birth_date"};
constexpr std::string_view EMPLOYMENT_DATE{"employment_date"};
constexpr std::string_view EMPLOYEE_NUMBER{"employee_number"};
constexpr std::string_view DEPARTMENT_ID{"department_id"};
constexpr std::string_view STAFF_POSITION_ID{"staff_position_id"};
constexpr std::string_view WORK_SCHEDULE_ID{"work_schedule_id"};

}  // namespace request_keys

application::AddEmployeeRequestDto EmployeeRequestHandler::makeAddEmployeeRequestDto(
    const json::object& request_body_as_object) const {
    application::AddEmployeeRequestDto add_employee_request_dto;

    add_employee_request_dto.last_name = request_body_as_object.at(request_keys::LAST_NAME).as_string();
    add_employee_request_dto.first_name = request_body_as_object.at(request_keys::FIRST_NAME).as_string();
    add_employee_request_dto.patronymic = request_body_as_object.at(request_keys::PATRONYMIC).as_string();
    add_employee_request_dto.birth_date = request_body_as_object.at(request_keys::BIRTH_DATE).as_string();
    add_employee_request_dto.employment_date = request_body_as_object.at(request_keys::EMPLOYMENT_DATE).as_string();
    add_employee_request_dto.employee_number = request_body_as_object.at(request_keys::EMPLOYEE_NUMBER).as_int64();
    add_employee_request_dto.department_id = request_body_as_object.at(request_keys::DEPARTMENT_ID).as_int64();
    add_employee_request_dto.staff_position_id = request_body_as_object.at(request_keys::STAFF_POSITION_ID).as_int64();
    add_employee_request_dto.work_schedule_id = request_body_as_object.at(request_keys::WORK_SCHEDULE_ID).as_int64();

    return add_employee_request_dto;
}