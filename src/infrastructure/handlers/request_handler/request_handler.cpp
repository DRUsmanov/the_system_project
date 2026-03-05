#include "request_handler.h"

#include <iostream>

namespace infrastructure {

StringResponse RequestHandler::MakeStringResponse(http::status status, std::string_view body, unsigned http_version, bool keep_alive, std::string_view content_type) {
    StringResponse response(status, http_version);
    response.set(http::field::content_type, content_type);
    response.body() = body;
    response.content_length(body.size());
    response.keep_alive(keep_alive);
    return response;
}

FileResponse RequestHandler::MakeFileResponse(http::status status, http::file_body::value_type&& file, unsigned http_version, bool keep_alive, std::string_view content_type){
    FileResponse response;
    response.version(http_version);
    response.result(status);
    response.insert(http::field::content_type, content_type);
    response.body() = std::move(file);
    response.prepare_payload();
    return response;
}

int HexToInt(char hex_digit) {
    if (hex_digit >= '0' && hex_digit <= '9') {
        return hex_digit - '0';
    } else if (hex_digit >= 'a' && hex_digit <= 'f') {
        return hex_digit - 'a' + 10;
    } else if (hex_digit >= 'A' && hex_digit <= 'F') {
        return hex_digit - 'A' + 10;
    }
    return 0;
}

std::string DecodeTarget(std::string_view encoded_target) {
    std::string decoded_target;
    decoded_target.reserve(encoded_target.length());

    for (size_t i = 0; i < encoded_target.length(); ++i) {
        if (encoded_target[i] == '%') {
            if (i + 2 < encoded_target.length()) {
                char hex1 = encoded_target[i + 1];
                char hex2 = encoded_target[i + 2];

                if (std::isxdigit(hex1) && std::isxdigit(hex2)) {
                    int value = HexToInt(hex1) * 16 + HexToInt(hex2);
                    decoded_target += static_cast<char>(value);
                    i += 2;
                } else {
                    decoded_target += encoded_target[i]; 
                }
            } else {
                decoded_target += encoded_target[i];
            }
        } else if (encoded_target[i] == '+') {
            decoded_target += ' ';
        } else {
            decoded_target += encoded_target[i];
        }
    }
    return decoded_target;
}

std::string_view RemoveLeadingSlash(std::string_view target){
    if (target.empty()){
        return target;
    }
    if (target[0] == '/'){
        target.remove_prefix(1);
    }
    if (!target.empty() && target.back() == '/'){
        target.remove_suffix(1);
    }
    return target;
}

std::string RequestHandler::PrepareTarget(std::string_view target){
    std::string decoded_target = DecodeTarget(target);
    std::string prepared_target = std::string(RemoveLeadingSlash(decoded_target));
    return prepared_target;
}

}  // namespace infrastructure
