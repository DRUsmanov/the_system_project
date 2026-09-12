#include "department_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {

}  // namespace request_keys

namespace response_keys { namespace get_department {
constexpr std::string_view STATUS{"status"};
constexpr std::string_view DEPARTMENTS{"departments"};
constexpr std::string_view ID{"id"};
constexpr std::string_view DESCRIPTION{"description"};
}}  // namespace response_keys::get_department

std::string infrastructure::DepartmentRequestHandler::makeGetDeratmentsResponse(
    std::optional<application::GetDepartmentsResponseDto> get_departments_response_dto) const {
    json::object response;
    if (get_departments_response_dto.has_value()) {
        response[response_keys::get_department::STATUS] = true;
        json::array departmetns_array;
        for (const auto& department : get_departments_response_dto.value().departmens) {
            json::object department_as_object;
            department_as_object[response_keys::get_department::ID] = department.first;
            department_as_object[response_keys::get_department::DESCRIPTION] = department.second;
            departmetns_array.push_back(department_as_object);
        }
        response[response_keys::get_department::DEPARTMENTS] = departmetns_array;
    } else {
        response[response_keys::get_department::STATUS] = false;
    }

    return serializeObject(response);
}
