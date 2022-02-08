#pragma once

#include <string>
#include "Operation.hpp"

namespace functions
{
class GetSelection : public Operation
{
public:
    GetSelection(std::string&, bool);
    ~GetSelection() = default;

    bool run(view::LogView&) const override;
    bool run(model::Log&) const override;

private:
    std::string& operationResult;
    bool shouldUnselect;
};
} // namespace functions
