#include "uow_factory_impl.h"

using namespace infrastructure;

std::shared_ptr<application::UowInterface> UowFactory::createUow() const {
    return std::make_shared<Uow>(connection_pool_.getConnection());
}