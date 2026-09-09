#include "factories_impl/uow_factory_impl/uow_factory_impl.h"

#include "logger.h"

using namespace infrastructure;

std::shared_ptr<application::UowInterface> UowFactory::createUow() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return std::make_shared<Uow>(connection_pool_.getConnection());
}