#include "department_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {
constexpr std::string_view DEPARTMENT_ID{"department_id"};
}  // namespace request_keys

namespace response_keys {
constexpr std::string_view DEPARTMENT_STAFF{"department_staff"};
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
constexpr std::string_view STATUS{"status"};
constexpr std::string_view DEPARTMENTS{"departments"};
constexpr std::string_view ID{"id"};
constexpr std::string_view DESCRIPTION{"description"};
}  // namespace response_keys

application::GetDepartmentStaffRequestDto infrastructure::DepartmentRequestHandler::makeGetDepartmentStaffRequestDto(
    std::string_view department_id_request) const {
    application::GetDepartmentStaffRequestDto get_department_staff_request_dto;
    department_id_request.remove_prefix(1);  // удаляем слэш
    auto department_id = std::stoi(std::string{department_id_request});
    get_department_staff_request_dto.department_id = department_id;
    return get_department_staff_request_dto;
}

std::string infrastructure::DepartmentRequestHandler::makeGetDepartmentStaffResponseDto(
    std::optional<application::GetDepartmentStaffResponseDto> get_department_staff_response_dto) const {
    json::object response;
    if (get_department_staff_response_dto.has_value()) {
        response[response_keys::STATUS] = true;
        json::array department_staff_array;
        for (const auto& data : get_department_staff_response_dto.value().data) {
            json::object data_as_object;
            data_as_object[response_keys::EMPLOYEE_ID] = data.employee_id;
            data_as_object[response_keys::LAST_NAME] = data.last_name;
            data_as_object[response_keys::FIRST_NAME] = data.first_name;
            data_as_object[response_keys::PATRONYMIC] = data.patronymic;
            data_as_object[response_keys::BIRTH_DATE] = data.birth_date;
            data_as_object[response_keys::EMPLOYMENT_DATE] = data.employment_date;
            data_as_object[response_keys::EMPLOYEE_NUMBER] = data.employee_number;
            data_as_object[response_keys::DEPARTMENT_ID] = data.department_id;
            data_as_object[response_keys::STAFF_POSITION_ID] = data.staff_position_id;
            data_as_object[response_keys::WORK_SCHEDULE_ID] = data.work_schedule_id;

            department_staff_array.push_back(data_as_object);
        }
        response[response_keys::DEPARTMENT_STAFF] = department_staff_array;
    } else {
        response[response_keys::STATUS] = false;
    }

    return serializeObject(response);
}

std::string infrastructure::DepartmentRequestHandler::makeGetDeratmentsResponse(
    std::optional<application::GetDepartmentsResponseDto> get_departments_response_dto) const {
    json::object response;
    if (get_departments_response_dto.has_value()) {
        response[response_keys::STATUS] = true;
        json::array departmetns_array;
        for (const auto& department : get_departments_response_dto.value().departmens) {
            json::object department_as_object;
            department_as_object[response_keys::ID] = department.first;
            department_as_object[response_keys::DESCRIPTION] = department.second;
            departmetns_array.push_back(department_as_object);
        }
        response[response_keys::DEPARTMENTS] = departmetns_array;
    } else {
        response[response_keys::STATUS] = false;
    }

    return serializeObject(response);
}
