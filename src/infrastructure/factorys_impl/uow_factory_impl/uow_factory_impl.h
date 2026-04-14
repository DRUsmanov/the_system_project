#pragma once

#include "application/factorys/uow_factory_interface.h"
#include "infrastructure/connection_pool/connection_pool.h"
#include "infrastructure/uow_impl/uow_impl.h"

namespace infrastructure {

class UowFactory : public application::UowFactoryInterface {
public:
    UowFactory(ConnectionPool& connection_pool)
    : connection_pool_{connection_pool} { }

    std::shared_ptr<application::UowInterface> CreateUow() const override;
private:
    ConnectionPool& connection_pool_;
};
    
} // namespace infrastructure
