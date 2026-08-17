#pragma once

namespace application {

class UowInterface {
public:
    virtual ~UowInterface() = default;

    virtual void commit() = 0;
};

}  // namespace application
