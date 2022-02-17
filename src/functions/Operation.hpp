#pragma once

namespace model
{
class Log;
} // namespace model

namespace functions
{
class Operation
{
public:
    virtual ~Operation() = default;
    virtual bool run(model::Log&) const = 0;
};
} // namespace functions
