#include "connection_pool.h"
#include "querys.h"

infrastructure::ConnectionPool::ConnectionWrapper infrastructure::ConnectionPool::GetConnection() {
    std::unique_lock lock{mutex_};

    cond_var_.wait(lock, [this] {
        return used_connections_ < pool_.size();
    });

    return {std::move(pool_[used_connections_++]), *this};
}

void infrastructure::ConnectionPool::ReturnConnection(ConnectionPool::ConnectionPtr&& conn) {
    {
        std::lock_guard lock{mutex_};
        assert(used_connections_ != 0);
        pool_[--used_connections_] = std::move(conn);
    }

    cond_var_.notify_one();
}

std::shared_ptr<pqxx::connection> infrastructure::ConnectionFactory::operator()() const{
    auto conn = std::make_shared<pqxx::connection>(db_url_);
    for (const auto& [query_name, query] : infrastructure::querys){
        conn->prepare(query_name, query);
    }
    return conn;
}