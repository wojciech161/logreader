#pragma once

#include <string>
#include "Operation.hpp"

namespace functions
{
class Find : public Operation
{
public:
    Find(const std::string&, bool);
    ~Find() = default;

    void run(view::LogView&) const override;

private:
    std::string query;
    bool caseSensitive;
};
} // namespace functions
