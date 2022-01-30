#pragma once

#include <functional>
#include <string>
#include "Operation.hpp"

namespace functions
{
class Grep : public Operation
{
public:
    Grep(const view::LogView&, const std::string&, bool, bool, bool);
    ~Grep() = default;

    void run(view::LogView&) const override;

private:
    const view::LogView& base;
    std::function<bool(const std::string&)> lineMatch;
};
} // namespace functions
