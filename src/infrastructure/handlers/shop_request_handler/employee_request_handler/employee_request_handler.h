#pragma once

#include <boost/beast.hpp>
#include <string_view>

#include "application_gateway/application_gateway_interface.h"
#include "application_gateway/dto/user_dto.h"
#include "content_type/content_types.h"
#include "json_formater/json_formater.h"
#include "token_manager/token_manager.h"

namespace infrastructure {

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

class EmployeeRequestHandler {
public:
    explicit EmployeeRequestHandler(application::ApplicationGatewayInterface& application_gateway) :
        application_gateway_{application_gateway} {}

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req,
                    TokenManager::Payload payload,
                    TextResponseMaker&& text_response_maker,
                    FileResponseMaker&& file_response_maker,
                    Send&& send) {
        std::string_view target = req.target();
        target.remove_prefix(API_V1_SHOP_EMPLOYEE.size());

        if (auto content_type_header_it = req.find(http::field::content_type);
            content_type_header_it == req.end() || content_type_header_it->value() != content_type::APP_JSON ||
            !target.empty()) {
            auto bad_request_response =
                text_response_maker(http::status::bad_request, BAD_REQUEST, content_type::APP_JSON);
            bad_request_response.set(http::field::cache_control, "no-cache");
            send(std::move(bad_request_response));
            return;
        }

        json::object request_body_as_object = parseString(std::string{req.body()});

        auto method = req.method();

        application::UserAccessDto user_access_dto;
        user_access_dto.user_id = payload.value().at(keys::USER_ID);

        if (method == http::verb::post) {
            auto add_employee_request_dto = makeAddEmployeeRequestDto(request_body_as_object);
            auto is_added = application_gateway_.addEmployee(user_access_dto, add_employee_request_dto);
            if (is_added) {
                auto employee_success_added_response =
                    text_response_maker(http::status::created, EMPLOYEE_SUCCESS_ADDED, content_type::APP_JSON);
                employee_success_added_response.set(http::field::cache_control, "no-cache");
                send(std::move(employee_success_added_response));
                return;
            } else {
                auto employee_failed_added_response =
                    text_response_maker(http::status::conflict, EMPLOYEE_FAILED_ADDED, content_type::APP_JSON);
                employee_failed_added_response.set(http::field::cache_control, "no-cache");
                send(std::move(employee_failed_added_response));
                return;
            }
        }

        if (method == http::verb::delete_) {
        }

        if (method == http::verb::patch) {
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
    application::AddEmployeeRequestDto makeAddEmployeeRequestDto(const json::object& request_body_as_object) const;

private:
    constexpr static std::string_view API_V1_SHOP_EMPLOYEE = "/api/v1/shop/employee"sv;
    constexpr static std::string_view EMPLOYEE_SUCCESS_ADDED = "{\"result\":true}";
    constexpr static std::string_view EMPLOYEE_FAILED_ADDED = "{\"result\":false}";
    constexpr static std::string_view BAD_REQUEST =
        "{\"code\":\"bad_request\", \"message\":\"Bad request from employee_request_handler\"}"sv;
    constexpr static std::string_view INVALID_METHOD =
        "{\"code\":\"invalidMethod\", \"message\":\"Only POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR =
        "{\"code\": \"server_error\", \"message\": \"Server error from employee_request_handler\"}"sv;
};

}  // namespace infrastructure
