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

class DepartmentRequestHandler {
public:
    explicit DepartmentRequestHandler(application::ApplicationGatewayInterface& application_gateway) :
        application_gateway_{application_gateway} {}

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req,
                    TokenManager::Payload payload,
                    TextResponseMaker&& text_response_maker,
                    FileResponseMaker&& file_response_maker,
                    Send&& send) {
        std::string_view target = req.target();
        target.remove_prefix(API_V1_SHOP_DEPARTMENT.size());

        auto method = req.method();

        application::UserAccessDto user_access_dto;
        user_access_dto.user_id = payload.value().at(keys::USER_ID);

        auto content_type_header_it = req.find(http::field::content_type);

        if (content_type_header_it == req.end()) {
            if (method == http::verb::get) {
                auto result = application_gateway_.getDepartments(user_access_dto);
                if (result.has_value()) {
                    auto departments_list_success_response = text_response_maker(http::status::ok,
                                                                                 makeGetDeratmentsResponse(result),
                                                                                 content_type::APP_JSON);
                    departments_list_success_response.set(http::field::cache_control, "no-cache");
                    send(std::move(departments_list_success_response));
                    return;
                } else {
                    auto departments_list_failed_response = text_response_maker(http::status::conflict,
                                                                                makeGetDeratmentsResponse(result),
                                                                                content_type::APP_JSON);
                    departments_list_failed_response.set(http::field::cache_control, "no-cache");
                    send(std::move(departments_list_failed_response));
                    return;
                }
            }
        } else {
            if (content_type_header_it->value() != content_type::APP_JSON || !target.empty()) {
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
    std::string makeGetDeratmentsResponse(
        std::optional<application::GetDepartmentsResponseDto> get_departments_response_dto) const;

private:
    constexpr static std::string_view API_V1_SHOP_DEPARTMENT = "/api/v1/shop/department"sv;
    constexpr static std::string_view BAD_REQUEST =
        "{\"code\":\"bad_request\", \"message\":\"Bad request from department_request_handler\"}"sv;
    constexpr static std::string_view INVALID_METHOD =
        "{\"code\":\"invalidMethod\", \"message\":\"Only GET, POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR =
        "{\"code\": \"server_error\", \"message\": \"Server error from department_request_handler\"}"sv;
};

}  // namespace infrastructure
