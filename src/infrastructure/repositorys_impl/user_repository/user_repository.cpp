#include "user_repository.h"
#include "infrastructure/connection_pool/querys.h"

using namespace infrastructure;

std::optional<domain::User> UserRepository::DownloadUser(const domain::UserLoginData &login_data) const {
    pqxx::work work(uow_->GetConnection());
    auto result = work.exec_params(query::download_user, login_data.login, login_data.password);

    if (result.size() != 1) {
        return std::nullopt;
    }

    domain::User user;

    user.user_id = result.at(0)[tables::users::ID].as<int>();
    user.employee_id = result.at(0)[tables::users::EMPLOYEE_ID].as<int>();
    user.permissions = result.at(0)[tables::users::PERMISSIONS].as<int64_t>();
    user.admin_category_id = result.at(0)[tables::users::ADMIN_CATEGORY].as<int>();

    return user;
}