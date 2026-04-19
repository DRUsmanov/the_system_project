#include "token_manager.h"

#include <exception>

using namespace infrastructure;

constexpr const char* SECRET_KEY{"dsdgjSDGpjkjaSF9935JSKJNg99121547y578JSDJGbjnbjbdg788734609dsgbiIDUHSGIUhn98"};

constexpr std::string USER_ID{"user_id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string ISSUER{"The system server"};
constexpr std::string TYPE{"JWT"};

TokenManager::Token TokenManager::CreateToken(int user_id, int employee_id) const {
    try {
        auto token = jwt::create()
        .set_issuer(ISSUER)
        .set_type(TYPE)
        .set_payload_claim(USER_ID, jwt::claim(std::to_string(user_id)))
        .set_payload_claim(EMPLOYEE_ID, jwt::claim(std::to_string(employee_id)))
        .sign(jwt::algorithm::hs256{SECRET_KEY});

        return token;
    }
    catch(const std::exception& ex){
        return std::nullopt;
    }
}

TokenManager::Payload TokenManager::GetPayloadFromToken(std::string token) const {
    try{
        auto decode_token = jwt::decode(token);
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{SECRET_KEY})
            .with_issuer(ISSUER);

        verifier.verify(decode_token);

        int user_id = std::stoi(decode_token.get_payload_claim(USER_ID).as_string());
        int employee_id = std::stoi(decode_token.get_payload_claim(EMPLOYEE_ID).as_string());

        std::unordered_map<std::string, int> payload;
        payload[USER_ID] = user_id;
        payload[EMPLOYEE_ID] = employee_id;

        return payload;
    }
    catch(const std::exception& ex){
        return std::nullopt;
    }
}
