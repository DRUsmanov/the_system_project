#include "token_manager/token_manager.h"

#include <exception>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/boost-json/defaults.h>

using namespace infrastructure;

constexpr const char* SECRET_KEY{"dsdgjSDGpjkjaSF9935JSKJNg99121547y578JSDJGbjnbjbdg788734609dsgbiIDUHSGIUhn98"};

TokenManager::Token TokenManager::createToken(uint64_t user_id, uint64_t employee_id) const {
    try {
        auto token = jwt::create()
                         .set_issuer(keys::ISSUER)
                         .set_type(keys::TYPE)
                         .set_payload_claim(keys::USER_ID, jwt::claim(std::to_string(user_id)))
                         .set_payload_claim(keys::EMPLOYEE_ID, jwt::claim(std::to_string(employee_id)))
                         .sign(jwt::algorithm::hs256{SECRET_KEY});

        return token;
    } catch (const std::exception& ex) {
        return std::nullopt;
    }
}

TokenManager::Payload TokenManager::getPayloadFromToken(std::string_view token) const {
    try {
        auto decode_token = jwt::decode(std::string(token));
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{SECRET_KEY}).with_issuer(keys::ISSUER);

        verifier.verify(decode_token);

        uint64_t user_id = std::stoi(decode_token.get_payload_claim(keys::USER_ID).as_string());
        uint64_t employee_id = std::stoi(decode_token.get_payload_claim(keys::EMPLOYEE_ID).as_string());

        std::unordered_map<std::string, uint64_t> payload;
        payload[keys::USER_ID] = user_id;
        payload[keys::EMPLOYEE_ID] = employee_id;

        return payload;
    } catch (const std::exception& ex) {
        return std::nullopt;
    }
}
