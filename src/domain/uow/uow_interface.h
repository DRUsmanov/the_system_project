#pragma once

namespace domain {

class UowInterface {
public:
    virtual ~UowInterface() = default;

    virtual void commit() = 0;
};

}  // namespace domain
