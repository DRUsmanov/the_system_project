#include "employee_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {
namespace add_employee {
constexpr std::string_view LAST_NAME{"last_name"};
constexpr std::string_view FIRST_NAME{"first_name"};
constexpr std::string_view PATRONYMIC{"patronymic"};
constexpr std::string_view BIRTH_DATE{"birth_date"};
constexpr std::string_view EMPLOYMENT_DATE{"employment_date"};
constexpr std::string_view EMPLOYEE_NUMBER{"employee_number"};
constexpr std::string_view DEPARTMENT_ID{"department_id"};
constexpr std::string_view STAFF_POSITION_ID{"staff_position_id"};
constexpr std::string_view WORK_SCHEDULE_ID{"work_schedule_id"};
}  // namespace add_employee

namespace remove_employee {
constexpr std::string_view EMPLOYEE_ID{"employee_id"};
}  // namespace remove_employee

}  // namespace request_keys

namespace response_keys {
namespace add_employee {
constexpr std::string_view IS_ADDED{"is_added"};
constexpr std::string_view EMPLOYEE_ID{"employee_id"};
}  // namespace add_employee

namespace remove_employee {
constexpr std::string_view IS_REMOVED{"is_removed"};
}  // namespace remove_employee

}  // namespace response_keys

application::AddEmployeeRequestDto EmployeeRequestHandler::makeAddEmployeeRequestDto(
    const json::object& request_body_as_object) const {
    application::AddEmployeeRequestDto add_employee_request_dto;

    add_employee_request_dto.last_name = request_body_as_object.at(request_keys::add_employee::LAST_NAME).as_string();
    add_employee_request_dto.first_name = request_body_as_object.at(request_keys::add_employee::FIRST_NAME).as_string();
    add_employee_request_dto.patronymic = request_body_as_object.at(request_keys::add_employee::PATRONYMIC).as_string();
    add_employee_request_dto.birth_date = request_body_as_object.at(request_keys::add_employee::BIRTH_DATE).as_string();
    add_employee_request_dto.employment_date =
        request_body_as_object.at(request_keys::add_employee::EMPLOYMENT_DATE).as_string();
    add_employee_request_dto.employee_number =
        request_body_as_object.at(request_keys::add_employee::EMPLOYEE_NUMBER).as_int64();
    add_employee_request_dto.department_id =
        request_body_as_object.at(request_keys::add_employee::DEPARTMENT_ID).as_int64();
    add_employee_request_dto.staff_position_id =
        request_body_as_object.at(request_keys::add_employee::STAFF_POSITION_ID).as_int64();
    add_employee_request_dto.work_schedule_id =
        request_body_as_object.at(request_keys::add_employee::WORK_SCHEDULE_ID).as_int64();

    return add_employee_request_dto;
}

std::string infrastructure::EmployeeRequestHandler::makeAddEmployeeResponse(
    std::optional<application::AddEmployeeResponseDto> add_employee_response_dto) const {
    json::object response;
    if (add_employee_response_dto.has_value()) {
        response[response_keys::add_employee::IS_ADDED] = true;
        response[response_keys::add_employee::EMPLOYEE_ID] = add_employee_response_dto.value().employee_id;
    } else {
        response[response_keys::add_employee::IS_ADDED] = false;
    }

    return serializeObject(response);
}

application::RemoveEmployeeRequestDto infrastructure::EmployeeRequestHandler::makeRemoveEmployeeRequestDto(
    const json::object& request_body_as_object) const {
    application::RemoveEmployeeRequestDto remove_employee_request_dto;
    remove_employee_request_dto.employee_id =
        request_body_as_object.at(request_keys::remove_employee::EMPLOYEE_ID).as_int64();
    return remove_employee_request_dto;
}

std::string infrastructure::EmployeeRequestHandler::makeRemoveEmployeeResponse(
    std::optional<application::RemoveEmployeeResponseDto> remove_employee_response_dto) const {
    json::object response;
    if (remove_employee_response_dto.has_value()) {
        response[response_keys::remove_employee::IS_REMOVED] = true;
    } else {
        response[response_keys::remove_employee::IS_REMOVED] = false;
    }

    return serializeObject(response);
}
