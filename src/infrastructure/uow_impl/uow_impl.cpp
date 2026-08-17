#include "uow_impl.h"

using namespace infrastructure;

pqxx::connection& Uow::getConnection() {
    return *connection_wrapper_;
}