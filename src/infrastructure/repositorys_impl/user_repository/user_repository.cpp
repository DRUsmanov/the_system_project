#include "user_repository.h"

#include "domain/entities/shop/employee/employee.h"
#include "domain/entities/timesheet/admin_categorys/admin_category.h"
#include "domain/entities/user/user.h"
#include "infrastructure/connection_pool/querys.h"

using namespace infrastructure;

std::optional<domain::User> UserRepository::loginUser(const domain::UserLoginData& user_login_data) const {
    pqxx::work work(uow_->getConnection());
    auto result = work.exec_params(query::LOGIN, user_login_data.login, user_login_data.password);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::User user;

    user.user_id = domain::UserId{result.at(0)[tables::users::ID].as<int>()};
    user.employee_id = domain::EmployeeId{result.at(0)[tables::users::EMPLOYEE_ID].as<int>()};
    user.admin_category_id = domain::AdminCategoryId{result.at(0)[tables::users::ADMIN_CATEGORY].as<int>()};

    return user;
}

std::optional<domain::User> UserRepository::downloadUser(const domain::UserId& user_id) const {
    pqxx::work work(uow_->getConnection());
    auto result = work.exec_params(query::DOWNLOAD_USER, *user_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::User user;

    user.user_id = domain::UserId{result.at(0)[tables::users::ID].as<int>()};
    user.employee_id = domain::EmployeeId{result.at(0)[tables::users::EMPLOYEE_ID].as<int>()};
    user.admin_category_id = domain::AdminCategoryId{result.at(0)[tables::users::ADMIN_CATEGORY].as<int>()};

    return user;
}
