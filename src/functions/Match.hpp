#pragma once

#include <functional>
#include <string>

namespace functions
{
std::function<bool(const std::string&)> createMatcher(const std::string& query, bool regexp, bool caseSensitive, bool inverted);
} // namespace functions
