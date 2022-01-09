#include "Match.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <regex>

namespace functions
{
template<typename charT = std::string::value_type>
struct caseInsensitiveChecker
{
    caseInsensitiveChecker() {}
    bool operator()(charT ch1, charT ch2)
    {
        return std::toupper(ch1) == std::toupper(ch2);
    }
};

std::function<bool(const std::string&)> createMatcher(const std::string& query, bool regexp, bool caseSensitive, bool inverted) try
{
    if (not regexp)
    {
        if (caseSensitive and not inverted)
        {
            return [query](const std::string& line) {
                return std::search(line.begin(), line.end(), query.begin(), query.end()) != line.end();
            };
        }
        else if (caseSensitive and inverted)
        {
            return [query](const std::string& line) {
                return std::search(line.begin(), line.end(), query.begin(), query.end()) == line.end();
            };
        }
        else if (not caseSensitive and not inverted)
        {
            return [query](const std::string& line) {
                return std::search(line.begin(), line.end(), query.begin(), query.end(), caseInsensitiveChecker()) != line.end();
            };
        }
        else // (not caseSensitive and inverted)
        {
            return [query](const std::string& line) {
                return std::search(line.begin(), line.end(), query.begin(), query.end(), caseInsensitiveChecker()) == line.end();
            };
        }
    }
    else // regexp
    {
        auto regexFlags = caseSensitive ?
            std::regex_constants::ECMAScript :
            std::regex_constants::ECMAScript | std::regex_constants::icase;
        std::regex regex{query, regexFlags};
        if (not inverted)
        {
            return [regex](const std::string& line) {
                return std::regex_search(line, regex);
            };
        }
        else // regex, inverted
        {
            return [regex](const std::string& line) {
                return not std::regex_search(line, regex);
            };
        }
    }
    return [](const std::string&) {return false;};
} catch(const std::exception& e)
{
    std::cout << "Error during matcher creation: " << e.what() << std::endl;
    return [](const std::string&) {return false;};
}
} // namespace functions
