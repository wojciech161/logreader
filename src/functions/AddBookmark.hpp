#pragma once

#include <string>
#include "Operation.hpp"

namespace functions
{
class AddBookmark : public Operation
{
public:
    AddBookmark(const std::string&);
    virtual ~AddBookmark() = default;

    bool run(view::LogView&) const override;

private:
    std::string bookmarkName;
};
} // namespace functions
