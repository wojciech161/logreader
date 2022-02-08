#pragma once

#include <string>
#include "Operation.hpp"

namespace functions
{
class OpenSingle : public Operation
{
public:
    OpenSingle(const std::string&);
    ~OpenSingle() = default;

    bool run(view::LogView&) const override;

private:
    std::string path;
};
} // namespace functions
