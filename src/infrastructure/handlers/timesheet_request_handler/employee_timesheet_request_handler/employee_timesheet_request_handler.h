#pragma once

#include <boost/beast.hpp>
#include <string_view>

#include "application_gateway/application_gateway_interface.h"
#include "content_type/content_types.h"
#include "json_formater/json_formater.h"
#include "token_manager/token_manager.h"

namespace infrastructure {

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

class EmployeeTimesheetRequestHandler {
public:
    explicit EmployeeTimesheetRequestHandler(application::ApplicationGatewayInterface& application_gateway) :
        application_gateway_{application_gateway} {}

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req,
                    TokenManager::Payload payload,
                    TextResponseMaker&& text_response_maker,
                    FileResponseMaker&& file_response_maker,
                    Send&& send) {
        std::string_view target = req.target();
        target.remove_prefix(API_V1_TIMESHEET_EMPLOYEE.size());

        auto method = req.method();

        application::UserAccessDto user_access_dto;
        user_access_dto.user_id = payload.value().at(keys::USER_ID);

        if (method == http::verb::get) {
        }

        auto content_type_header_it = req.find(http::field::content_type);

        if (content_type_header_it == req.end() || content_type_header_it->value() != content_type::APP_JSON) {
            auto bad_request_response =
                text_response_maker(http::status::bad_request, BAD_REQUEST, content_type::APP_JSON);
            bad_request_response.set(http::field::cache_control, "no-cache");
            send(std::move(bad_request_response));
            return;
        }

        json::object request_body_as_object = parseString(std::string{req.body()});

        if (method == http::verb::post) {
        }

        if (method == http::verb::delete_) {
        }

        if (method == http::verb::patch) {
            if (target.starts_with(DAYS_DATA)) {
                auto update_employee_timesheet_request_dto =
                    makeUpdateEmployeeDaysDataRequestDto(request_body_as_object);
                auto result =
                    application_gateway_.updateEmployeeTimesheetDaysData(user_access_dto,
                                                                         update_employee_timesheet_request_dto);
                if (result) {
                    auto success_updated_employee_timesheet_days_data_response =
                        text_response_maker(http::status::ok,
                                            makeUpdateEmployeeTimesheetDaysDataResponse(result),
                                            content_type::APP_JSON);
                    success_updated_employee_timesheet_days_data_response.set(http::field::cache_control, "no-cache");
                    send(std::move(success_updated_employee_timesheet_days_data_response));
                    return;
                } else {
                    auto failed_updated_employee_timesheet_days_data_response =
                        text_response_maker(http::status::conflict,
                                            makeUpdateEmployeeTimesheetDaysDataResponse(result),
                                            content_type::APP_JSON);
                    failed_updated_employee_timesheet_days_data_response.set(http::field::cache_control, "no-cache");
                    send(std::move(failed_updated_employee_timesheet_days_data_response));
                    return;
                }
            } else if (target.starts_with(LEAVE_TYPE)) {
            } else if (target.starts_with(ASSIGNMENT)) {
            }
        }

        auto invalid_method_response =
            text_response_maker(http::status::method_not_allowed, INVALID_METHOD, content_type::APP_JSON);
        invalid_method_response.set(http::field::allow, "POST, DELETE, PATCH");
        invalid_method_response.set(http::field::cache_control, "no-cache");
        send(std::move(invalid_method_response));
        return;
    }

private:
    application::ApplicationGatewayInterface& application_gateway_;

private:
    application::UpdateEmployeeTimesheetDaysDataRequestDto makeUpdateEmployeeDaysDataRequestDto(
        const json::object& request_body_as_object) const;
    std::string makeUpdateEmployeeTimesheetDaysDataResponse(bool is_employee_timesheet_days_data_updated) const;

private:
    constexpr static std::string_view API_V1_TIMESHEET_EMPLOYEE = "/api/v1/timesheet/employee/"sv;
    constexpr static std::string_view DAYS_DATA = "days_data"sv;
    constexpr static std::string_view LEAVE_TYPE = "leave_type"sv;
    constexpr static std::string_view ASSIGNMENT = "assignment"sv;
    constexpr static std::string_view BAD_REQUEST =
        "{\"code\":\"bad_request\", \"message\":\"Bad request from employee_timesheet_request_handler\"}"sv;
    constexpr static std::string_view INVALID_METHOD =
        "{\"code\":\"invalidMethod\", \"message\":\"Only POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR =
        "{\"code\": \"server_error\", \"message\": \"Server error from employee_timesheet_request_handler\"}"sv;
};

}  // namespace infrastructure
