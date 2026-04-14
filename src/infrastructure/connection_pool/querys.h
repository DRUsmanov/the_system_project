#include <unordered_map>
#include <string>

namespace infrastructure {


namespace query {

constexpr std::string download_user{"download_user"};

} // namespace query

namespace tables {

namespace users {

constexpr std::string ID{"id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string LOGIN{"login"};
constexpr std::string PASSWORD{"password"};
constexpr std::string PERMISSIONS{"permissions"};
constexpr std::string ADMIN_CATEGORY{"admin_category_id"};
    
} // namespace use 

    
} // namespace table 



inline const std::unordered_map<std::string, std::string> querys{
    {download_user, R"(SELECT id, employee_id, permissions, admin_category_id FROM users WHERE login = $1 AND password = $2;)"}
};

} // namespace infrastructure
