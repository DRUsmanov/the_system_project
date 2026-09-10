#pragma once

#include <memory>

#include "uow/uow_interface.h"

namespace domain {

class UowFactoryInterface {
public:
    virtual ~UowFactoryInterface() = default;

    virtual std::shared_ptr<UowInterface> createUow() const = 0;
};

}  // namespace domain
