#pragma once

#include <boost/beast.hpp>
#include <boost/url/url_view.hpp>
#include <iostream>
#include <string_view>

#include "application_gateway/application_gateway_interface.h"
#include "content_type/content_types.h"
#include "handlers/timesheet_request_handler/work_schedule_request_handler/work_schedule_request_handler.h"
#include "json_formater/json_formater.h"
#include "token_manager/token_manager.h"

namespace infrastructure {

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

class TimesheetRequestHandler {
public:
    explicit TimesheetRequestHandler(application::ApplicationGatewayInterface& application_gateway) :
        application_gateway_{application_gateway}, work_schedule_request_handler_{application_gateway} {}

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req,
                    TokenManager::Payload payload,
                    TextResponseMaker&& text_response_maker,
                    FileResponseMaker&& file_response_maker,
                    Send&& send) {
        std::string_view target = req.target();
        auto params = boost::urls::url_view(target).params();
        target.remove_prefix(API_V1_TIMESHEET.size());

        if (target.starts_with(WORK_SCHEDULE)) {
            work_schedule_request_handler_(std::move(req),
                                           payload,
                                           text_response_maker,
                                           file_response_maker,
                                           std::forward<decltype(send)>(send));
            return;
        }

        auto method = req.method();

        if (method == http::verb::get) {
            auto department_id_it = params.find(DEPARTMENT_ID);
            auto year_it = params.find(YEAR);
            auto month_it = params.find(MONTH);
            if (department_id_it != params.end() && year_it != params.end() && month_it != params.end()) {
                application::GetDepartmentTimesheetRequestDto get_department_timesheet_request_dto;
                get_department_timesheet_request_dto.department_id =
                    static_cast<uint64_t>(std::stoll((*department_id_it).value));
                get_department_timesheet_request_dto.year = static_cast<int>(std::stoi((*year_it).value));
                get_department_timesheet_request_dto.month = static_cast<uint>(std::stoi((*month_it).value));

                application::UserAccessDto user_access_dto;
                user_access_dto.user_id = payload.value().at(keys::USER_ID);

                auto result =
                    application_gateway_.getDepartmentTimesheet(user_access_dto, get_department_timesheet_request_dto);

                if (result.has_value()) {
                    auto timesheet_success_response = text_response_maker(http::status::ok,
                                                                          makeGetDepartmentTimesheetResponse(result),
                                                                          content_type::APP_JSON);
                    timesheet_success_response.set(http::field::cache_control, "no-cache");
                    send(std::move(timesheet_success_response));
                    return;
                } else {
                    auto workschedules_list_failed_response =
                        text_response_maker(http::status::internal_server_error,
                                            makeGetDepartmentTimesheetResponse(result),
                                            content_type::APP_JSON);
                    workschedules_list_failed_response.set(http::field::cache_control, "no-cache");
                    send(std::move(workschedules_list_failed_response));
                    return;
                }

            } else {
                auto invalid_params_request =
                    text_response_maker(http::status::bad_request, INVALID_PARAMS, content_type::APP_JSON);
                invalid_params_request.set(http::field::cache_control, "no-cache");
                send(std::move(invalid_params_request));
                return;
            }
        }

        if (method == http::verb::post) {
        }

        if (method == http::verb::delete_) {
        }

        if (method == http::verb::patch) {
        }
    }

private:
    application::ApplicationGatewayInterface& application_gateway_;
    WorkscheduleRequestHandler work_schedule_request_handler_;

private:
    std::string makeGetDepartmentTimesheetResponse(
        std::optional<application::GetDepartmentTimesheetResponseDto> get_department_timesheet_response_dto);

private:
    constexpr static std::string_view API_V1_TIMESHEET = "/api/v1/timesheet/"sv;
    constexpr static std::string_view WORK_SCHEDULE = "work_schedule"sv;
    constexpr static std::string_view DEPARTMENT_ID = "department_id"sv;
    constexpr static std::string_view YEAR = "year"sv;
    constexpr static std::string_view MONTH = "month"sv;

    constexpr static std::string_view UNAUTHORIZED = "{\"code\":\"unauthorized\", \"message\":\"Bad token\"}"sv;
    constexpr static std::string_view BAD_REQUEST =
        "{\"code\":\"bad_request\", \"message\":\"Bad request from timesheet_request_handler\"}"sv;
    constexpr static std::string_view INVALID_METHOD =
        "{\"code\":\"invalidMethod\", \"message\":\"Only POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view INVALID_PARAMS = "{\"code\":\"invalidParams\", \"message\":\"Invalid params\"}"sv;
    constexpr static std::string_view SERVER_ERROR = "{\"code\": \"server_error\", \"message\": \"Server error\"}"sv;
};

}  // namespace infrastructure
