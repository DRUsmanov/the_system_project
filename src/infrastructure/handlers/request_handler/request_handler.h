#pragma once

#include "infrastructure/handlers/login_request_handler/login_request_handler.h"
#include "infrastructure/handlers/shop_request_handler/shop_request_handler.h"
#include "infrastructure/logger/logger.h"
#include "infrastructure/url_decoder/url_decoder.h"
#include "infrastructure/token_manager/token_manager.h"
#include "application/application_manager_interface.h"
#include "infrastructure/handlers/file_sender/file_sender.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/url/url_view.hpp>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <chrono>
#include <variant>
#include <exception>

namespace infrastructure {

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

using StringRequest = http::request<http::string_body>;
using StringResponse = http::response<http::string_body>;
using FileResponse = http::response<http::file_body>;
using Response = std::variant<std::monostate, StringResponse, FileResponse>;

/**
 * @brief Добавляет к обработчику запросов логирование
 */

template <typename SomeRequestHandler>
class LoggingRequestHandler{
public:
    LoggingRequestHandler(SomeRequestHandler& handler)
    : handler_{handler}{ }

    template <typename Body, typename Allocator, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send, const beast::tcp_stream& stream){
        logger::LogRequest(req, stream);

        auto request_processing_start_time = std::chrono::steady_clock::now();
        handler_(std::move(req), [send, request_processing_start_time](auto&& response){
            auto request_processing_end_time = std::chrono::steady_clock::now();
            auto request_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(request_processing_end_time - request_processing_start_time);
            logger::LogResponse(response, request_processing_time.count());
            send(std::move(response));
        });
    }
private:
    SomeRequestHandler& handler_;
};

/**
 * @brief Определяет тип запроса и передает его специализированному обработчику
 */
class RequestHandler {
public:
    using Strand = net::strand<net::io_context::executor_type>;

    explicit RequestHandler(
        const application::ApplicationManagerInterface& application_manager
        , const FileSender& file_sender    
    )
    : token_manager_{std::make_shared<TokenManager>()}
    , login_request_handler_{application_manager, token_manager_, file_sender}
    , shop_request_handler_{application_manager, token_manager_, file_sender} { }

    RequestHandler(const RequestHandler&) = delete;
    RequestHandler& operator=(const RequestHandler&) = delete;

    template <typename Body, typename Allocator, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        const auto text_response_maker = [this, version = req.version(), keep_alive = req.keep_alive()]
        (http::status status, std::string_view text, std::string_view content_type = content_type::APP_JSON){
            return MakeStringResponse(status, text, version, keep_alive, content_type);
        };

        const auto file_response_maker = [this, version = req.version(), keep_alive = req.keep_alive()]
        (http::status status, http::file_body::value_type&& file, std::string_view content_type){
            return MakeFileResponse(status, std::move(file), version, keep_alive, content_type);
        };

        try {
            std::string decoded_target = DecodeUrl(req.target());
            req.target(decoded_target);

            std::string path = boost::urls::url_view{decoded_target}.path();

            if (path == API_V1_LOGIN) {
                login_handler_(std::move(req), text_response_maker, file_response_maker, std::forward<decltype(send)>(send));
                return;
            }
            if (path == API_V1_SHOP){
                shop_request_handler_(std::move(req), text_response_maker, file_response_maker, std::forward<decltype(send)>(send));
                return;
            }
        }
        catch(const std::exception& ex) {
            auto server_error = text_response_maker(http::status::internal_server_error, SERVER_ERROR, content_type::APP_JSON);
            server_error.set(http::field::cache_control, "no-cache");
            send(std::move(server_error));
            return;
        }
    }

private:
    StringResponse MakeStringResponse(http::status status, std::string_view body, unsigned http_version,
        bool keep_alive, std::string_view content_type);
    FileResponse MakeFileResponse(http::status status, http::file_body::value_type&& file, unsigned http_version,
        bool keep_alive, std::string_view content_type);

    std::shared_ptr<TokenManager> token_manager_;
    LoginRequestHandler login_request_handler_;
    ShopRequestHandler shop_request_handler_;

    constexpr static std::string_view API_V1_LOGIN = "/api/v1/login"sv;
    constexpr static std::string_view API_V1_SHOP = "/api/v1/shop"sv;
    constexpr static std::string_view SERVER_ERROR = "{\"code\": \"server_error\", \"message\": \"Server error\"}"sv;
};

}  // namespace infrastructure
