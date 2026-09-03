#pragma once

#include <memory>

#include "uow/uow_interface.h"

namespace application {

class UowFactoryInterface {
public:
    virtual ~UowFactoryInterface() = default;

    virtual std::shared_ptr<UowInterface> createUow() const = 0;
};

}  // namespace application
