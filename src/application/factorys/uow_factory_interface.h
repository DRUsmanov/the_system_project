#pragma once

#include "application/uow/uow_interface.h"

#include <memory>

namespace application {

class UowFactoryInterface {
public:
    virtual ~UowFactoryInterface() = default;

    virtual std::shared_ptr<UowInterface> CreateUow() const = 0;
};
    
} // namespace application


