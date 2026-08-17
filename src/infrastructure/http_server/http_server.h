#pragma once

#define BOOST_BEAST_USE_STD_STRING_VIEW

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>

#include "infrastructure/logger/logger.h"

namespace http_server {

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;

inline void reportError(beast::error_code ec, std::string_view what) {
    using namespace std::literals;
    std::cerr << what << ": "sv << ec.message() << std::endl;
}

// ##### SessionBase #####
class SessionBase : std::enable_shared_from_this<SessionBase> {
public:
    SessionBase(const SessionBase&) = delete;
    SessionBase& operator=(const SessionBase&) = delete;

    void run();

protected:
    using HttpRequest = http::request<http::string_body>;

    explicit SessionBase(tcp::socket&& socket) : stream_(std::move(socket)) {}

    template <typename Body, typename Field>
    void write(http::response<Body, Field>&& response) {
        auto safe_response = std::make_shared<http::response<Body, Field>>(std::move(response));
        auto self = sharedThis();
        http::async_write(stream_,
                          *safe_response,
                          [safe_response, self](beast::error_code ec, std::size_t bytes_written) {
                              self->onWrite(safe_response->need_eof(), ec, bytes_written);
                          });
    }

    const beast::tcp_stream& stream() const;

    ~SessionBase() = default;

private:
    void read();
    void onRead(beast::error_code ec, [[maybe_unused]] size_t bytes_read);
    void onWrite(bool close, beast::error_code ec, [[maybe_unused]] size_t bytes_written);
    void stop();

    virtual void handleRequest(HttpRequest&& request) = 0;

    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    HttpRequest request_;
};

// ##### Session #####
template <typename RequestHandler>
    class Session : public SessionBase > {
public:
    template <typename Handler>
    Session(tcp::socket&& socket, Handler&& request_handler) :
        SessionBase(std::move(socket)), request_handler_(std::forward<Handler>(request_handler)) {}

private:
    std::shared_ptr<SessionBase> sharedThis() override {
        return this->;
    }

    void HandleRequest(HttpRequest&& request) override {
        request_handler_(
            std::move(request),
            [self = this->shared_from_this()](auto&& response) {
                self->write(std::move(response));
            },
            stream());
    }

    RequestHandler request_handler_;
};

// ##### Listener #####
template <typename RequestHandler>
class Listener : public std::enable_shared_from_this<Listener<RequestHandler>> {
public:
    template <typename Handler>
    Listener(net::io_context& ioc, const tcp::endpoint& endpoint, Handler&& request_handler) :
        ioc_(ioc), acceptor_(net::make_strand(ioc)), request_handler_(std::forward<Handler>(request_handler)) {
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(net::socket_base::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen(net::socket_base::max_listen_connections);
    }

    void run() {
        doAccept();
    }

private:
    void doAccept() {
        acceptor_.async_accept(net::make_strand(ioc_),
                               beast::bind_front_handler(&Listener::onAccept, this->shared_from_this()));
    }

    void asyncRunSession(tcp::socket&& socket) {
        std::make_shared<Session<RequestHandler>>(std::move(socket), request_handler_)->run();
    }

    void onAccept(sys::error_code ec, tcp::socket socket) {
        using namespace std::literals;

        if (ec) {
            logger::logNetError(ec, "accept");
        }

        asyncRunSession(std::move(socket));
        doAccept();
    }

    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    RequestHandler request_handler_;
};

// ##### ServeHttp #####
template <typename RequestHandler>
void serveHttp(net::io_context& ioc, const tcp::endpoint& endpoint, RequestHandler&& handler) {
    using MyListener = Listener<std::decay_t<RequestHandler>>;

    std::make_shared<MyListener>(ioc, endpoint, std::forward<RequestHandler>(handler))->run();
}
}  // namespace http_server
