#include <string>
#include <unordered_map>

namespace infrastructure {

namespace query {

constexpr std::string LOGIN{"login"};
constexpr std::string DOWNLOAD_USER{"dload_user"};
constexpr std::string DOWNLOAD_USER_PERMISSIONS{"dload_user_permissions"};
constexpr std::string UPLOAD_EMPLOYEE{"upld_employee"};
constexpr std::string DOWNLOAD_EMPLOYEE_BY_EMPLOYEE_NUMBER{"dload_employee_by_num"};
constexpr std::string DOWNLOAD_EMPLOYEE_BY_EMPLOYEE_ID{"dload_employee_by_id"};
constexpr std::string UPLOAD_EMPLOYEE_ASSIGNMENT{"upld_employee_asgnmt"};
constexpr std::string DOWNLOAD_STAFF_POSITION{"dload_staff_position"};
constexpr std::string UPLOAD_EMPLOYEE_PROFESSIONS{"upload_employee_prof"};
constexpr std::string DOWNLOAD_PRE_HOLIDAYS_BY_YEAR{"dload_pre_hdays_year"};
constexpr std::string DOWNLOAD_HOLIDAYS_BY_YEAR{"dload_hdays_year"};
constexpr std::string DOWNLOAD_EXTRA_HOLIDAYS_BY_YEAR{"dload_extra_hdays_year"};
constexpr std::string DOWNLOAD_SYSTEM_ADMINISTRATOR_ID{"dload_sysadmin_id"};
constexpr std::string DOWNLOAD_WORK_SCHEDULE{"dload_work_schedule"};
constexpr std::string DOWNLOAD_VACATIONS_BY_YEAR{"dload_vacations_year"};
constexpr std::string DOWNLOAD_EMPLOYEE_VACATIONS_BY_YEAR{"dload_vac_empl_year"};
constexpr std::string UPLOAD_TIMESHEET{"upload_timesheet"};
constexpr std::string DOWNLOAD_EMPLOYEE_ASSIGNMENT{"dload_empl_assignment"};
constexpr std::string REMOVE_EMPLOYEE{"rm_employee"};
constexpr std::string DOWNLOAD_DEPARTMENTS{"dload_departments"};
constexpr std::string DOWNLOAD_STAFF_POSITIONS{"dload_staff_positions"};
constexpr std::string DOWNLOAD_WORK_SCHEDULES{"dload_work_schedules"};
constexpr std::string DOWNLOAD_DEPARTMENT_ASSIGNMENTS{"dload_dep_assignments"};
constexpr std::string UPDATE_EMPLOYEE{"upd_employee"};
constexpr std::string UPDATE_EMPLOYEE_ASSIGNMENT{"upd_empl_assig"};

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

namespace staff_positions {
constexpr std::string ID{"id"};
constexpr std::string DESCRIPTION{"description"};
constexpr std::string DEFAULT_PROFESSION_ID{"default_profession_id"};
}  // namespace staff_positions

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

namespace pre_holidays {
constexpr std::string ID{"id"};
constexpr std::string DATE{"date"};
}  // namespace pre_holidays

namespace holidays {
constexpr std::string ID{"id"};
constexpr std::string DATE{"date"};
}  // namespace holidays

namespace extra_holidays {
constexpr std::string ID{"id"};
constexpr std::string DATE{"date"};
}  // namespace extra_holidays

namespace admin_categorys {
constexpr std::string ID{"id"};
constexpr std::string CATEGORY{"category"};
}  // namespace admin_categorys

namespace work_schedules {
constexpr std::string ID{"id"};
constexpr std::string WORK_SCHEDULE{"work_schedule"};
constexpr std::string DESCRIPTION{"description"};
}  // namespace work_schedules

namespace vacations {
constexpr std::string ID{"id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string START_DATE{"start_date"};
constexpr std::string END_DATE{"end_date"};
}  // namespace vacations

namespace timesheet {
constexpr std::string ID{"id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string DEPARTMENT_ID{"department_id"};
constexpr std::string STAFF_POSITION_ID{"staff_position_id"};
constexpr std::string DATE{"date"};
constexpr std::string WORK_TIME{"work_time"};
constexpr std::string NIGHT_WORK_TIME{"night_work_time"};
constexpr std::string COMMENT{"comment"};
constexpr std::string WORK_START{"work_start"};
constexpr std::string WORK_END{"work_end"};
constexpr std::string NIGHT_WORK_START{"night_work_start"};
constexpr std::string NIGHT_WORK_END{"night_work_end"};
constexpr std::string REST_START{"rest_start"};
constexpr std::string REST_END{"rest_end"};
constexpr std::string LEAVE_TYPE{"leave_type"};
constexpr std::string ADMIN_CATEGORY_ID{"admin_category_id"};
constexpr std::string ADMIN_EMPLOYEE_ID{"admin_employee_id"};
}  // namespace timesheet

namespace departments {
constexpr std::string ID{"id"};
constexpr std::string DESCRIPTION{"description"};
}  // namespace departments

}  // namespace tables

// TODO: переделать на запросы через имена столбцов
inline const std::unordered_map<std::string, std::string> querys{
    {query::LOGIN, R"(SELECT id, employee_id, admin_category_id FROM users WHERE login = $1 AND password = $2;)"},
    {query::DOWNLOAD_USER, R"(SELECT id, employee_id, admin_category_id FROM users WHERE id = $1;)"},
    {query::DOWNLOAD_USER_PERMISSIONS,
     R"(SELECT id, user_id, department_id, permissions FROM permissions WHERE user_id = $1;)"},
    {query::UPLOAD_EMPLOYEE,
     R"(INSERT INTO employees (last_name, first_name, patronymic, birth_date, employment_date, employee_number)
     VALUES ($1, $2, $3, $4, $5, $6) RETURNING id;)"},
    {query::DOWNLOAD_EMPLOYEE_BY_EMPLOYEE_ID,
     R"(SELECT id, last_name, first_name, patronymic, birth_date, employment_date, employee_number
     FROM employees WHERE id = $1;)"},
    {query::DOWNLOAD_EMPLOYEE_BY_EMPLOYEE_NUMBER,
     R"(SELECT id, last_name, first_name, patronymic, birth_date, employment_date, employee_number
     FROM employees WHERE employee_number = $1;)"},
    {query::UPLOAD_EMPLOYEE_ASSIGNMENT,
     R"(INSERT INTO staffing_assignments (employee_id, department_id, staff_position_id, work_schedule_id)
     VALUES ($1, $2, $3, $4) RETURNING id;)"},
    {query::DOWNLOAD_STAFF_POSITION, R"(SELECT * FROM staff_positions WHERE id = $1;)"},
    {query::UPLOAD_EMPLOYEE_PROFESSIONS,
     R"(INSERT INTO employees_professions (employee_id, profession_id) VALUES ($1, $2) RETURNING id;)"},
    {query::DOWNLOAD_PRE_HOLIDAYS_BY_YEAR,
     R"(SELECT id, date FROM pre_holidays WHERE date >= MAKE_DATE($1, 1, 1) AND date < MAKE_DATE($1 + 1, 1, 1) ORDER BY date;)"},
    {query::DOWNLOAD_HOLIDAYS_BY_YEAR,
     R"(SELECT id, date FROM holidays WHERE date >= MAKE_DATE($1, 1, 1) AND date < MAKE_DATE($1 + 1, 1, 1) ORDER BY date;)"},
    {query::DOWNLOAD_EXTRA_HOLIDAYS_BY_YEAR,
     R"(SELECT id, date FROM extra_holidays WHERE date >= MAKE_DATE($1, 1, 1) AND date < MAKE_DATE($1 + 1, 1, 1) ORDER BY date;)"},
    {query::DOWNLOAD_SYSTEM_ADMINISTRATOR_ID, R"(SELECT id, category FROM admin_categorys WHERE category = 'system';)"},
    {query::DOWNLOAD_WORK_SCHEDULE, R"(SELECT * FROM work_schedules WHERE id = $1;)"},
    {query::DOWNLOAD_VACATIONS_BY_YEAR, R"(SELECT id, employee_id, start_date, end_date FROM vacations
     WHERE start_date >= MAKE_DATE($1, 1, 1) AND start_date < MAKE_DATE($1 + 1, 1, 1);)"},
    {query::DOWNLOAD_EMPLOYEE_VACATIONS_BY_YEAR, R"(SELECT id, employee_id, start_date, end_date FROM vacations
     WHERE employee_id = $1 AND start_date >= MAKE_DATE($2, 1, 1)
     AND start_date < MAKE_DATE($2 + 1, 1, 1);)"},
    {query::UPLOAD_TIMESHEET,
     R"(INSERT INTO timesheet (employee_id, department_id, staff_position_id, date, work_start, work_end, work_time,
     night_work_start, night_work_end, night_work_time, rest_start, rest_end, leave_type, admin_category_id, admin_employee_id, comment)
     VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16) RETURNING id;)"},
    {query::DOWNLOAD_EMPLOYEE_ASSIGNMENT,
     R"(SELECT id, employee_id, department_id, staff_position_id, work_schedule_id FROM staffing_assignments
     WHERE employee_id = $1;)"},
    {query::REMOVE_EMPLOYEE, R"(DELETE FROM employees WHERE id=$1;)"},
    {query::DOWNLOAD_DEPARTMENTS, R"(SELECT * FROM departments ORDER BY description ASC;)"},
    {query::DOWNLOAD_STAFF_POSITIONS, R"(SELECT * FROM staff_positions ORDER BY id ASC;)"},
    {query::DOWNLOAD_WORK_SCHEDULES, R"(SELECT * FROM work_schedules ORDER BY description ASC;)"},
    {query::DOWNLOAD_DEPARTMENT_ASSIGNMENTS, R"(SELECT * FROM staffing_assignments WHERE department_id=$1;)"},
    {query::UPDATE_EMPLOYEE,
     R"(UPDATE employees SET last_name=$2, first_name=$3, patronymic=$4, birth_date=$5, employment_date=$6, employee_number=$7 WHERE id=$1;)"},
    {query::UPDATE_EMPLOYEE_ASSIGNMENT,
     R"(UPDATE staffing_assignments SET department_id=$2, staff_position_id=$3, work_schedule_id=$4 WHERE id=$1;)"}};

}  // namespace infrastructure
