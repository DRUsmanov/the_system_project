#include "http_server.h"

using namespace infrastructure;

using namespace std::literals;

// ##### SessionBase #####
void SessionBase::run() {
    net::dispatch(stream_.get_executor(), beast::bind_front_handler(&SessionBase::read, shared_from_this()));
}

void SessionBase::read() {
    request_ = {};
    stream_.expires_after(30s);
    http::async_read(stream_, buffer_, request_, beast::bind_front_handler(&SessionBase::onRead, shared_from_this()));
}

void SessionBase::onRead(beast::error_code ec, [[maybe_unused]] std::size_t bytes_read) {
    if (ec == http::error::end_of_stream) {
        return stop();
    }

    if (ec) {
        reportError(ec, "read"sv);
        return;
    }

    handleRequest(std::move(request_));
}

void SessionBase::onWrite(bool close, beast::error_code ec, [[maybe_unused]] std::size_t bytes_written) {
    if (ec) {
        reportError(ec, "write"sv);
        return;
    }

    if (close) {
        stop();
        return;
    }

    read();
}

void SessionBase::stop() {
    beast::error_code ec;
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
    if (ec) {
        return reportError(ec, "close"sv);
    }
}

const beast::tcp_stream& SessionBase::stream() const {
    return stream_;
}
