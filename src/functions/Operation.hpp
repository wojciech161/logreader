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
    virtual void run(view::LogView&) const = 0;
};
} // namespace functions
