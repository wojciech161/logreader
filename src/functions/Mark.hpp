#pragma once

#include <string>
#include "Operation.hpp"

namespace functions
{
class Mark : public Operation
{
public:
    Mark(const std::string&);
    ~Mark() = default;

    void run(view::LogView&) const override;

private:
    std::string query;
};
} // namespace functions
