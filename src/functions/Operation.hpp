#pragma once

namespace view
{
class LogView;
} // namespace view

namespace functions
{
class Operation
{
public:
    virtual ~Operation() = default;
    virtual bool run(view::LogView&) const = 0;
};
} // namespace functions
