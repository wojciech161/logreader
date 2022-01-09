#pragma once

#include <string>

namespace view
{
class LogView;
} // namespace view

namespace functions
{
class Find
{
public:
    Find(const std::string&, bool);
    ~Find() = default;

    void run(view::LogView&);

private:
    std::string query;
    bool caseSensitive;
};
} // namespace functions
