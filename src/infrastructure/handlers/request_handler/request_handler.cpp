#include "request_handler.h"

#include <iostream>

namespace infrastructure {

StringResponse RequestHandler::MakeStringResponse(http::status status, std::string_view body,
                                                    unsigned http_version, bool keep_alive, std::string_view content_type) {
    StringResponse response(status, http_version);
    response.set(http::field::content_type, content_type);
    response.body() = body;
    response.content_length(body.size());
    response.keep_alive(keep_alive);
    return response;
}

FileResponse RequestHandler::MakeFileResponse(http::status status, http::file_body::value_type&& file,
                                                unsigned http_version, bool keep_alive, std::string_view content_type){
    FileResponse response;
    response.version(http_version);
    response.result(status);
    response.insert(http::field::content_type, content_type);
    response.body() = std::move(file);
    response.prepare_payload();
    return response;
}

}  // namespace infrastructure
