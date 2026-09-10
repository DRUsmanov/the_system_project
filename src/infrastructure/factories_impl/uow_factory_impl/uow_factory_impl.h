#pragma once

#include "connection_pool/connection_pool.h"
#include "factories/uow_factory_interface.h"
#include "uow_impl/uow_impl.h"

namespace infrastructure {

class UowFactory : public domain::UowFactoryInterface {
public:
    UowFactory(ConnectionPool& connection_pool) : connection_pool_{connection_pool} {}

    std::shared_ptr<domain::UowInterface> createUow() const override;

private:
    ConnectionPool& connection_pool_;
};

}  // namespace infrastructure
