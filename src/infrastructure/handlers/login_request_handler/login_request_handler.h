#pragma once

#include "application/application_manager_interface.h"
#include "infrastructure/json_formater/json_formater.h"
#include "application/dto/user_dto.h"
#include "infrastructure/token_manager/token_manager.h"
#include "infrastructure/handlers/file_sender/file_sender.h"

#include <boost/beast.hpp>
#include <string_view>
#include <memory>

namespace infrastructure{

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

/**
 * @brief Обрабатывает запросы аутентификации пользователя, авторизованные пользователи перенаправляются на главную страницу
 */
class LoginRequestHandler{
public:
    explicit LoginRequestHandler(
        const application::ApplicationManagerInterface& application_manager
        , const std::shared_ptr<TokenManager> token_manager
        , const FileSender& file_sender
    )
    : application_manager_{application_manager}
    , token_manager_{token_manager}
    , file_sender_{file_sender} { }

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, TokenManager::Payload payload,
                    TextResponseMaker&& text_response_maker, FileResponseMaker&& file_response_maker, Send&& send){     
        
        if (payload.has_value()){
            file_sender_(FileSender::File::INDEX_HTML, std::forward<decltype(text_response_maker)>(text_response_maker),
                        std::forward<decltype(file_response_maker)>(file_response_maker), std::forward<decltype(send)>(send));
            return;
        }

        std::string_view target = req.target();
        target.remove_prefix(API_V1_LOGIN.size());

        if (auto content_type_header_it = req.find(http::field::content_type);
            content_type_header_it == req.end() || content_type_header_it->value() != content_type::APP_JSON || !target.empty()) {
            auto bad_request_response = text_response_maker(http::status::bad_request, BAD_REQUEST, content_type::APP_JSON);
            bad_request_response.set(http::field::cache_control, "no-cache");
            send(std::move(bad_request_response));
            return;
        }
        
        if (auto method = req.method(); method != http::verb::post){
            auto invalid_method_response = text_response_maker(http::status::method_not_allowed, INVALID_METHOD, content_type::APP_JSON);
            invalid_method_response.set(http::field::allow, "POST");
            invalid_method_response.set(http::field::cache_control, "no-cache");
            send(std::move(invalid_method_response));
            return;
        }

        json::object request_body_as_object = ParseString(std::string(req.body));

        application::UserLoginInputDto user_login_input_dto;
        user_login_input_dto.login = std::string(request_body_as_object.at(LOGIN).as_string());
        user_login_input_dto.password = std::string(request_body_as_object.at(PASSWORD).as_string());

        auto user_login_output_dto = application_manager_.Login(user_login_input_dto);
        
        if (!user_login_output_dto.has_value()) {
            auto unauthorized_response = text_response_maker(http::status::unauthorized, UNAUTHORIZED, content_type::APP_JSON);
            unauthorized_response.set(http::field::cache_control, "no-cache");
            send(std::move(unauthorized_response));
            return;
        }

        auto token = token_manager_->CreateToken(user_login_output_dto->user_id, user_login_output_dto->employee_id );

        if (!token.has_value()){
            auto unauthorized_response = text_response_maker(http::status::unauthorized, UNAUTHORIZED, content_type::APP_JSON);
            unauthorized_response.set(http::field::cache_control, "no-cache");
            send(std::move(unauthorized_response));
            return;
        }

        auto authorized_response = text_response_maker(http::status::accepted, MakeAcceptedAnswer(token), content_type::APP_JSON);
        authorized_response.set(http::field::cache_control, "no-cache");
        send(std::move(authorized_response));
        return;
    }
private:
    const application::ApplicationManagerInterface& application_manager_;
    const std::shared_ptr<TokenManager> token_manager_;
    const FileSender& file_sender_;

    constexpr static std::string_view LOGIN = "login"sv;
    constexpr static std::string_view PASSWORD = "password"sv;
    constexpr static std::string_view API_V1_LOGIN = "/api/v1/login"sv;
    constexpr static std::string_view UNAUTHORIZED = "{\"code\":\"unauthorized\", \"message\":\"Bad login or password\"}"sv;
    constexpr static std::string_view BAD_REQUEST = "{\"code\":\"bad_request\", \"message\":\"Bad request\"}"sv;
    constexpr static std::string_view INVALID_METHOD = "{\"code\":\"invalid_method\", \"message\":\"Only POST method is expected\"}"sv;
    
    std::string MakeAcceptedAnswer(const TokenManager::Token& token){
        return "{\"auth_token\":\"" + *token + "\"}";
    }
};

} // namespace infrastructure

