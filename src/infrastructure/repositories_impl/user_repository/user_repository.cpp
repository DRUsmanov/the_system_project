#include "repositories_impl/user_repository/user_repository.h"

#include <cstdint>

#include "connection_pool/querys.h"
#include "entities/shop/employee/employee.h"
#include "entities/timesheet/admin_categorys/admin_category.h"
#include "entities/user/user.h"

using namespace infrastructure;

std::optional<domain::User> UserRepository::loginUser(std::string login, std::string password) const {
    auto result = uow_->execParams(query::LOGIN, login, password);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::User user;

    user.user_id = domain::UserId{result.at(0)[tables::users::ID].as<uint64_t>()};
    user.employee_id = domain::EmployeeId{result.at(0)[tables::users::EMPLOYEE_ID].as<uint64_t>()};
    user.admin_category_id = domain::AdminCategoryId{result.at(0)[tables::users::ADMIN_CATEGORY].as<uint64_t>()};

    return user;
}

std::optional<domain::User> UserRepository::downloadUser(const domain::UserId& user_id) const {
    auto result = uow_->execParams(query::DOWNLOAD_USER, *user_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::User user;

    user.user_id = domain::UserId{result.at(0)[tables::users::ID].as<uint64_t>()};
    user.employee_id = domain::EmployeeId{result.at(0)[tables::users::EMPLOYEE_ID].as<uint64_t>()};
    user.admin_category_id = domain::AdminCategoryId{result.at(0)[tables::users::ADMIN_CATEGORY].as<uint64_t>()};

    return user;
}
