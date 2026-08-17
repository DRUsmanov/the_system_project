#pragma once

#include <string>
#include <unordered_map>

#include "domain/entities/permission/permission.h"
#include "domain/entities/shop/department/department.h"
#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/timesheet/admin_categorys/admin_category.h"
#include "utils/tagged.h"

namespace domain {

namespace detail {
struct UserIdTag {};
}  // namespace detail

using UserId = utils::Tagged<int, detail::UserIdTag>;
using UserIdHasher = utils::TaggedHasher<UserId>;
using UserPermissions = std::unordered_map<DepartmentId, Permissions, DepartmentIdHasher>;

struct User {
    UserId user_id;
    EmployeeId employee_id;
    UserPermissions permissions;
    AdminCategoryId admin_category_id;
};

struct UserLoginData {
    std::string login;
    std::string password;
};

}  // namespace domain
