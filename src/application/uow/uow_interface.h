#pragma once

namespace application {

class UowInterface {
public:
    virtual ~UowInterface() = default;

    virtual void Commit() = 0;
};    
    
} // namespace application
