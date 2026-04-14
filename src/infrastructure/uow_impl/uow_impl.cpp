#include "uow_impl.h"

using namespace infrastructure;

pqxx::connection& Uow::GetConnection() {
    return *connection_wrapper_;
}