#include "NameCreator.hpp"

namespace functions
{
std::string createName(const std::string& path)
{
    auto const pos = path.find_last_of('/');
    const auto leaf = path.substr(pos+1);
    return leaf;
}

std::string createName(const std::string& query, bool regexp, bool caseSensitive, bool inverted)
{
    std::string options{"."};
    options += regexp ? "R" : "r";
    options += caseSensitive ? "C" : "c";
    options += inverted ? "I" : "i";
    return query + options;
}
} // namespace functions
