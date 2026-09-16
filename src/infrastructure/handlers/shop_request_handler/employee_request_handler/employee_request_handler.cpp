#include "employee_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {
constexpr std::string_view IS_ASSIGNMENT_CHANGED{"is_assignment_changed"};
constexpr std::string_view ASSIGNMENT_CHANGING_DATE{"assignment_changing_date"};
constexpr std::string_view EMPLOYEE_ID{"employee_id"};
constexpr std::string_view LAST_NAME{"last_name"};
constexpr std::string_view FIRST_NAME{"first_name"};
constexpr std::string_view PATRONYMIC{"patronymic"};
constexpr std::string_view BIRTH_DATE{"birth_date"};
constexpr std::string_view EMPLOYMENT_DATE{"employment_date"};
constexpr std::string_view EMPLOYEE_NUMBER{"employee_number"};
constexpr std::string_view DEPARTMENT_ID{"department_id"};
constexpr std::string_view STAFF_POSITION_ID{"staff_position_id"};
constexpr std::string_view WORK_SCHEDULE_ID{"work_schedule_id"};
constexpr std::string_view REMOVING_DATE{"removing_date"};
}  // namespace request_keys

namespace response_keys {
constexpr std::string_view IS_ADDED{"is_added"};
constexpr std::string_view EMPLOYEE_ID{"employee_id"};
constexpr std::string_view IS_REMOVED{"is_removed"};
constexpr std::string_view IS_UPDATED{"is_updated"};
}  // namespace response_keys

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

std::string EmployeeRequestHandler::makeAddEmployeeResponse(
    std::optional<application::AddEmployeeResponseDto> add_employee_response_dto) const {
    json::object response;
    if (add_employee_response_dto.has_value()) {
        response[response_keys::IS_ADDED] = true;
        response[response_keys::EMPLOYEE_ID] = add_employee_response_dto.value().employee_id;
    } else {
        response[response_keys::IS_ADDED] = false;
    }

    return serializeObject(response);
}

application::RemoveEmployeeRequestDto EmployeeRequestHandler::makeRemoveEmployeeRequestDto(
    const json::object& request_body_as_object) const {
    application::RemoveEmployeeRequestDto remove_employee_request_dto;
    remove_employee_request_dto.employee_id = request_body_as_object.at(request_keys::EMPLOYEE_ID).as_int64();
    remove_employee_request_dto.removing_date = request_body_as_object.at(request_keys::REMOVING_DATE).as_string();
    return remove_employee_request_dto;
}

std::string EmployeeRequestHandler::makeRemoveEmployeeResponse(bool is_employee_removed) const {
    json::object response;
    response[response_keys::IS_REMOVED] = is_employee_removed;
    return serializeObject(response);
}

application::UpdateEmployeeRequestDto infrastructure::EmployeeRequestHandler::makeUpdateEmployeeRequestDto(
    const json::object& request_body_as_object) const {
    application::UpdateEmployeeRequestDto update_employee_request_dto;

    update_employee_request_dto.employee_id = request_body_as_object.at(request_keys::EMPLOYEE_ID).as_int64();
    update_employee_request_dto.last_name = request_body_as_object.at(request_keys::LAST_NAME).as_string();
    update_employee_request_dto.first_name = request_body_as_object.at(request_keys::FIRST_NAME).as_string();
    update_employee_request_dto.patronymic = request_body_as_object.at(request_keys::PATRONYMIC).as_string();
    update_employee_request_dto.birth_date = request_body_as_object.at(request_keys::BIRTH_DATE).as_string();
    update_employee_request_dto.employment_date = request_body_as_object.at(request_keys::EMPLOYMENT_DATE).as_string();
    update_employee_request_dto.employee_number = request_body_as_object.at(request_keys::EMPLOYEE_NUMBER).as_int64();
    update_employee_request_dto.department_id = request_body_as_object.at(request_keys::DEPARTMENT_ID).as_int64();
    update_employee_request_dto.staff_position_id =
        request_body_as_object.at(request_keys::STAFF_POSITION_ID).as_int64();
    update_employee_request_dto.work_schedule_id = request_body_as_object.at(request_keys::WORK_SCHEDULE_ID).as_int64();

    if (!request_body_as_object.at(request_keys::ASSIGNMENT_CHANGING_DATE).is_null()) {
        update_employee_request_dto.assignment_changing_date =
            request_body_as_object.at(request_keys::ASSIGNMENT_CHANGING_DATE).as_string();
    }

    return update_employee_request_dto;
}

std::string infrastructure::EmployeeRequestHandler::makeUpdateEmployeeResponse(bool is_employee_updated) const {
    json::object response;
    response[response_keys::IS_UPDATED] = is_employee_updated;
    return serializeObject(response);
}
