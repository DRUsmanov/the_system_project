#pragma once

#include "application/uow/uow_interface.h"
#include "infrastructure/connection_pool/connection_pool.h"

namespace infrastructure {

class Uow : public application::UowInterface {
public:
    Uow(ConnectionPool::ConnectionWrapper&& connection_wrapper)
    : connection_wrapper_{std::move(connection_wrapper)} { }

    pqxx::connection& GetConnection();
private:
    ConnectionPool::ConnectionWrapper connection_wrapper_;
};
    
} // namespace infrastructure


