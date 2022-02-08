#pragma once

namespace view
{
class LogView;
} // namespace view
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
    virtual bool run(view::LogView&) const = 0;
    virtual bool run(model::Log&) const = 0;
};
} // namespace functions
