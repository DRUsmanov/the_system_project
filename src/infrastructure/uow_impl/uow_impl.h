#pragma once

#include <memory>
#include <pqxx/pqxx>

#include "application/uow/uow_interface.h"
#include "infrastructure/connection_pool/connection_pool.h"

namespace infrastructure {

class Uow : public application::UowInterface {
public:
    Uow(ConnectionPool::ConnectionWrapper&& connection_wrapper) :
        connection_wrapper_{std::move(connection_wrapper)}, work_{*connection_wrapper_} {}

    Uow(const Uow&) = delete;
    Uow& operator=(const Uow&) = delete;
    Uow(Uow&&) = default;
    Uow& operator=(Uow&&) = default;

    void commit() override;

    template <typename... Args>
    pqxx::result execParams(const std::string& query, Args&&... args) {
        return work_.exec_params(query, std::forward<Args>(args)...);
    }

private:
    ConnectionPool::ConnectionWrapper connection_wrapper_;
    pqxx::work work_;
};

}  // namespace infrastructure
