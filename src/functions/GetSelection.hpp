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

    void run(view::LogView&) const override;

private:
    std::string& operationResult;
    bool shouldUnselect;
};
} // namespace functions
