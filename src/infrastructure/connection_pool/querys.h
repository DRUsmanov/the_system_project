#include <string>
#include <unordered_map>

namespace infrastructure {

namespace query {

constexpr std::string LOGIN{"login"};
constexpr std::string DOWNLOAD_USER{"dload_user"};
constexpr std::string DOWNLOAD_USER_PERMISSIONS{"dload_user_permissions"};
constexpr std::string UPLOAD_EMPLOYEE{"upld_employee"};
constexpr std::string UPLOAD_EMPLOYEE_ASSIGNMENT{"upld_employee_asgnmt"};
constexpr std::string DOWNLOAD_DEFAULT_PROFESSION{"dload_default_prof"};
constexpr std::string UPLOAD_EMPLOYEE_PROFESSIONS{"upload_employee_prof"};

}  // namespace query

namespace tables {

namespace users {
constexpr std::string ID{"id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string LOGIN{"login"};
constexpr std::string PASSWORD{"password"};
constexpr std::string ADMIN_CATEGORY{"admin_category_id"};
}  // namespace users

namespace employees {
constexpr std::string ID{"id"};
constexpr std::string LAST_NAME{"last_name"};
constexpr std::string FIRST_NAME{"first_name"};
constexpr std::string PATRONYMIC{"patronymic"};
constexpr std::string BIRTH_DATE{"birth_date"};
constexpr std::string EMPLOYMENT_DATE{"employment_date"};
constexpr std::string EMPLOYEE_NUMBER{"employee_number"};
}  // namespace employees

namespace permissions {
constexpr std::string ID{"id"};
constexpr std::string USER_ID{"user_id"};
constexpr std::string DEPARTMENT_ID{"department_id"};
constexpr std::string PERMISSIONS{"permissions"};
}  // namespace permissions

namespace staffing_assignments {
constexpr std::string ID{"id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string DEPARTMENT_ID{"department_id"};
constexpr std::string STAFF_POSITION_ID{"staff_position_id"};
constexpr std::string WORK_SCHEDULE_ID{"work_schedule_id"};
}  // namespace staffing_assignments

namespace professions {
constexpr std::string ID{"id"};
constexpr std::string PROFESSION{"profession"};
}  // namespace professions

namespace employees_professions {
constexpr std::string ID{"id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string PROFESSION_ID{"profession_id"};
}  // namespace employees_professions

}  // namespace tables

// TODO: переделать на запросы через имена столбцов
inline const std::unordered_map<std::string, std::string> querys{
    {query::LOGIN, R"(SELECT id, employee_id, admin_category_id FROM users WHERE login = $1 AND password = $2;)"},
    {query::DOWNLOAD_USER, R"(SELECT id, employee_id, admin_category_id FROM users WHERE id = $1;)"},
    {query::DOWNLOAD_USER_PERMISSIONS,
     R"(SELECT id, user_id, department_id, permissions FROM permissions WHERE user_id = $1;)"},
    {query::UPLOAD_EMPLOYEE,
     R"(INSERT INTO employees (last_name, first_name, patronymic, birth_date, employment_date, employee_number) VALUES ($1, $2, $3, $4, $5, $6) RETURNING id;)"},
    {query::UPLOAD_EMPLOYEE_ASSIGNMENT,
     R"(INSERT INTO staffing_assignments (employee_id, department_id, staff_position_id, work_schedule_id) VALUES ($1, $2, $3, $4) RETURNING id;)"},
    {query::DOWNLOAD_DEFAULT_PROFESSION, R"(SELECT default_profession_id FROM staff_positions WHERE id = $1;)"},
    {query::UPLOAD_EMPLOYEE_PROFESSIONS,
     R"(INSERT INTO employees_professions (employee_id, profession_id) VALUES ($1, $2) RETURNING id;)"}};

}  // namespace infrastructure
