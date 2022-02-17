#pragma once

#include <functional>
#include <string>
#include "Operation.hpp"

namespace functions
{
class Grep : public Operation
{
public:
    Grep(const model::Log&, const std::string&, bool, bool, bool);
    ~Grep() = default;

    bool run(model::Log&) const override;

private:
    const model::Log& base;
    std::function<bool(const std::string&)> lineMatch;
};
} // namespace functions
