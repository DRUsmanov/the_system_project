#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "entities/permission/permission.h"
#include "entities/shop/department/department.h"
#include "entities/shop/employee/employee.h"
#include "entities/timesheet/admin_categorys/admin_category.h"
#include "tagged.h"

namespace domain {

namespace detail {
struct UserIdTag {};
}  // namespace detail

using UserId = utils::Tagged<uint64_t, detail::UserIdTag>;
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
