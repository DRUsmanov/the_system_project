#pragma once

#include "application/application_manager_interface.h"
#include "infrastructure/token_manager/token_manager.h"
#include "infrastructure/json_formater/json_formater.h"
#include "application/dto/shop_dto.h"
#include "infrastructure/handlers/file_sender/file_sender.h"

#include <boost/beast.hpp>
#include <string_view>

namespace infrastructure{

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

/**
 * @brief Обрабатывает запросы с сущностями подразделения
 */
class ShopRequestHandler{
public:
    explicit ShopRequestHandler(
        const application::ApplicationManagerInterface& application_manager
        , const std::shared_ptr<TokenManager> token_manager
        , const FileSender& file_sender
    )
    : application_manager_{application_manager}
    , token_manager_{token_manager}
    , file_sender_{file_sender} { }

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, TextResponseMaker&& text_response_maker,
                    FileResponseMaker&& file_response_maker, Send&& send){
        auto authorization_field_it = req.find(http::field::authorization);
        
        if (authorization_field_it == req.end()) {
            file_sender_(FileSender::File::LOGIN_HTML, std::forward<decltype(text_response_maker)>(text_response_maker),
            std::forward<decltype(file_response_maker)>(file_response_maker), std::forward<decltype(send)>(send));
            return;
        }

        std::string_view token = authorization_field_it->value();
        TokenManager::Payload payload = token_manager_->GetPayloadFromToken(token);

        if (!payload){
            file_sender_(FileSender::File::LOGIN_HTML, std::forward<decltype(text_response_maker)>(text_response_maker),
                            std::forward<decltype(file_response_maker)>(file_response_maker), std::forward<decltype(send)>(send));
            return;
        }
            
        std::string_view target = req.target();

        if (target.empty()){
            auto bad_request_response = text_response_maker(http::status::bad_request, BAD_REQUEST, content_type::APP_JSON);
            bad_request_response.set(http::field::cache_control, "no-cache");
            send(std::move(bad_request_response));
            return;
        }
        
        target.remove_prefix(API_V1_SHOP.size());

        if (auto content_type_header_it = req.find(http::field::content_type);
            content_type_header_it == req.end() || content_type_header_it->value() != content_type::APP_JSON || target.empty()) {
            auto bad_request_response = text_response_maker(http::status::bad_request, BAD_REQUEST, content_type::APP_JSON);
            bad_request_response.set(http::field::cache_control, "no-cache");
            send(std::move(bad_request_response));
            return;
        }
        
        if (auto method = req.method(); method != http::verb::post || method != http::verb::delete_ || method != http::verb::patch) {
            auto invalid_method_response = text_response_maker(http::status::method_not_allowed, INVALID_METHOD, content_type::APP_JSON);
            invalid_method_response.set(http::field::allow, "POST, DELETE, PATCH");
            invalid_method_response.set(http::field::cache_control, "no-cache");
            send(std::move(invalid_method_response));
            return;
        }

        json::object request_body_as_object = ParseString(std::string(req.body));

        if (target == EMPLOYEE) {
            
        }
    }
private:
    const application::ApplicationManagerInterface& application_manager_;
    const std::shared_ptr<TokenManager> token_manager_;
    const FileSender& file_sender_;

    constexpr static std::string_view API_V1_SHOP = "/api/v1/shop/"sv;
    constexpr static std::string_view EMPLOYEE = "employee"sv;
    
    constexpr static std::string_view UNAUTHORIZED = "{\"code\":\"unauthorized\", \"message\":\"Bad token\"}"sv;
    constexpr static std::string_view BAD_REQUEST = "{\"code\":\"bad_request\", \"message\":\"Bad request\"}"sv;
    constexpr static std::string_view INVALID_METHOD = "{\"code\":\"invalidMethod\", \"message\":\"Only POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR = "{\"code\": \"server_error\", \"message\": \"Server error\"}"sv;

    void ProcessEmployeeRequest(){

    }
};

} // namespace infrastructure

